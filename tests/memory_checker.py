#!/usr/bin/env python3

import argparse
import enum
import json
import re
from os import path
from subprocess import run

from termcolor import colored

CONFIG_FILE_NAME = 'config.json'
BINARY_FILE_NAME = '42sh'
VALGRIND_DEFAULT_ARGUMENTS = ['--child-silent-after-fork=yes', '--leak-check=full', '--show-leak-kinds=all', '--track-origins=yes']
VALGRIND_COMMAND_NAME = 'valgrind'

PARSER = argparse.ArgumentParser('42sh Memory Checker')
PARSER.add_argument('-c', '--color', action='store_true', help='enables the color in output')
PARSER.add_argument('-t', '--trace', action='store_true', help='shows the full valgrind trace for showed tests')
PARSER.add_argument('-p', '--passed', '--show-passed', action='store_true', help='shows passed memory checks tests')
PARSER.add_argument('--only-on', default=None, type=int, help='executes memory check only on passed index of configuration file')


class Summary(enum.Enum):
    ERROR = 'ERROR'
    LEAK = 'LEAK'
    HEAP = 'HEAP'


class MemoryCheckResult:
    logs: list[str]
    errors: int
    allocs: int
    frees: int
    allocated_bytes: int
    leaked_bytes: int
    leaked_blocks: int
    allocation_delta: int

    def __init__(self, valgrind_logs: list[str]):
        self.logs = valgrind_logs
        self.error_summary_index = find_summary_index_in_logs(Summary.ERROR, self.logs)
        self.heap_summary_index = find_summary_index_in_logs(Summary.HEAP, self.logs)
        self.leak_summary_index = find_summary_index_in_logs(Summary.LEAK, self.logs)
        self.parse_heap_usage()
        self.parse_leaked_memory()
        self.parse_errors()
        self.compute_allocation_delta()

    def parse_errors(self) -> None:
        self.errors = int(self.logs[self.error_summary_index].split()[3].replace(',', ''))

    def parse_leaked_memory(self) -> None:
        leak_memory_line = self.logs[self.heap_summary_index + 1].split()
        self.leaked_bytes = int(leak_memory_line[5].replace(',', ''))
        self.leaked_blocks = int(leak_memory_line[8].replace(',', ''))

    def parse_heap_usage(self) -> None:
        heap_usage_line = self.logs[self.heap_summary_index + 2].split()
        self.allocs = int(heap_usage_line[4].replace(',', ''))
        self.frees = int(heap_usage_line[6].replace(',', ''))
        self.allocated_bytes = int(heap_usage_line[8].replace(',', ''))

    def compute_allocation_delta(self):
        self.allocation_delta = self.allocs - self.frees


def get_tests(filepath: str) -> any:
    with open(filepath) as json_file:
        return json.load(json_file)["tests"]


def get_valgrind_logs(command: str, binary_path: str) -> any:
    joined_valgrind_arguments = ' '.join(VALGRIND_DEFAULT_ARGUMENTS);
    to_execute = f'echo "{command}" | {VALGRIND_COMMAND_NAME} {joined_valgrind_arguments} {binary_path}'

    return run(to_execute, shell=True, capture_output=True, text=True)


def get_valgrind_pid_from_logs(valgrind_logs: list[str]) -> int:
    return int(valgrind_logs[0].split(' ')[0].strip('=='))


def format_valgrind_logs(unformatted_valgrind_logs: any) -> list[str]:
    return str(unformatted_valgrind_logs).split('\n')[:-1]


def find_summary_index_in_logs(summary_type: Summary, valgrind_logs: list[str]) -> int:
    valgrind_pid = get_valgrind_pid_from_logs(valgrind_logs)
    for index, log in enumerate(valgrind_logs):
        if re.match(rf'=={valgrind_pid}== {summary_type.value} SUMMARY:.*', log):
            return index
    return -1


def print_colored_or_not(message: str, color: str, colorize: bool):
    print(colored(message, color) if colorize else message)


def print_result(result: MemoryCheckResult, test: any, colorize: bool, show_valgrind_trace: bool, show_passed: bool, index: int) -> bool:
    passing = (result.errors == 0) and (result.allocation_delta == 0) and (result.leaked_bytes == 0)
    if passing and not show_passed:
        return True
    if passing:
        print_colored_or_not(f'#{index} {test["name"]} [{test["command"]}] has no memory issues.', 'green', colorize)
        if show_valgrind_trace:
            print_colored_or_not('=' * 50, 'green', colorize)
            print_colored_or_not('\n'.join(result.logs), 'green', colorize)
            print_colored_or_not('=' * 50, 'green', colorize)
        print()
        return True
    print_colored_or_not(f'#{index} {test["name"]} [{test["command"]}] has memory issues.', 'red', colorize)
    if not show_valgrind_trace:
        print_colored_or_not(f'Run with --trace --only-on {index} for details', 'red', colorize)

    if result.allocation_delta > 0:
        print_colored_or_not(f'- Missing {result.allocation_delta} free(s).', 'red', colorize)
    elif result.allocation_delta < 0:
        print_colored_or_not(f'- Too many free(s): {result.allocation_delta} too much.', 'red', colorize)

    if result.leaked_bytes > 0:
        print_colored_or_not(f'- {result.leaked_bytes} bytes in {result.leaked_blocks} blocks are leaking.', 'red', colorize)

    if result.errors - result.leaked_blocks > 0:
        print_colored_or_not(f'- {result.errors} others errors were found (run with --trace for details)', 'red', colorize)

    if show_valgrind_trace:
        print_colored_or_not('=' * 50, 'red', colorize)
        print_colored_or_not('\n'.join(result.logs), 'red', colorize)
        print_colored_or_not('=' * 50, 'red', colorize)
    print()
    return False


def run_memory_checker() -> int:
    args = PARSER.parse_args()
    tests = get_tests(path.dirname(path.realpath(__file__)) + path.sep + CONFIG_FILE_NAME)
    not_passing_checks = 0
    if args.only_on is None:
        for i, test in enumerate(tests):
            logs = format_valgrind_logs(get_valgrind_logs(test['command'], f'./{BINARY_FILE_NAME}').stderr)
            result = MemoryCheckResult(logs)
            passing = print_result(result, test, args.color, args.trace, args.passed, i)
            not_passing_checks += 1 if not passing else 0
        color = 'green' if not_passing_checks == 0 else 'yel<low' if not_passing_checks >= len(tests) / 2 else 'red'
        print_colored_or_not(f'Ran {len(tests)} ({len(tests) > - not_passing_checks} passed and {not_passing_checks} failed)', color, args.color)
    elif args.only_on < 0 or args.only_on not in range(len(tests)):
        print_colored_or_not(f'Error: Index {args.only_on} is not a valid index', 'yellow', args.color)
        return -1
    else:
        test = tests[args.only_on]
        logs = format_valgrind_logs(get_valgrind_logs(test['command'], f'./{BINARY_FILE_NAME}').stderr)
        result = MemoryCheckResult(logs)
        not_passing_checks += 1 if not print_result(result, test, args.color, args.trace, True, args.only_on) else 0
    return not_passing_checks


if __name__ == '__main__':
    exit(run_memory_checker())
