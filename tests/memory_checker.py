#!/usr/bin/env python3

import argparse
import enum
import json
import re
from os import path
from subprocess import run


class Summary(enum.Enum):
    ERROR = 'ERROR'
    LEAK = 'LEAK'
    HEAP = 'HEAP'


CONFIG_FILE_NAME = 'config.json'
BINARY_FILE_NAME = '42sh'
VALGRIND_DEFAULT_ARGUMENTS = ['--child-silent-after-fork=yes', '--leak-check=full', '--show-leak-kinds=all']
VALGRIND_COMMAND_NAME = 'valgrind'

PARSER = argparse.ArgumentParser('42sh Memory Checker')
PARSER.add_argument('-c', '--color', action='store_true', help='enables the color in output')
PARSER.add_argument('-t', '--trace', action='store_true', help='shows the full valgrind trace for showed tests')
PARSER.add_argument('-p', '--passed', '--show-passed', action='store_true', help='shows passed memory checks tests')


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


if __name__ == '__main__':
    args = PARSER.parse_args()
    tests = get_tests(path.dirname(path.realpath(__file__)) + path.sep + CONFIG_FILE_NAME)
    for test in tests:
        logs = format_valgrind_logs(get_valgrind_logs(test['command'], f'./{BINARY_FILE_NAME}').stderr)
        heap_summary_index = find_summary_index_in_logs(Summary.HEAP, logs)
        error_summary_index = find_summary_index_in_logs(Summary.ERROR, logs)
        leak_summary_index = find_summary_index_in_logs(Summary.LEAK, logs)
        print(test['name'])
        print('\n'.join(logs[heap_summary_index:heap_summary_index + 3]))
        if leak_summary_index != -1:
            print('\n'.join(logs[leak_summary_index:leak_summary_index + 6]))
        print(logs[error_summary_index])
        if test is not tests[-1]:
            print()
