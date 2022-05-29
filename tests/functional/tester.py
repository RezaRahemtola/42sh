#!/usr/bin/env python
from json import load as load_json
from subprocess import run
from sys import argv
from termcolor import colored
from os import path
from difflib import unified_diff as diff
from glob import glob


def get_tests():
    folder = path.dirname(path.realpath(__file__))
    data = []

    for file in glob(folder + '/src/**/*.json', recursive=True):
        with open(file) as json_file:
            data += load_json(json_file)["tests"]
    return data


def run_command(command: str, piped_path: str):
    return run(f'echo -e "{command}" | {piped_path} ; echo Exit status:$?', shell=True, capture_output=True, text=True)


def disp_err(tcsh, mysh) -> None:
    if tcsh.stdout != mysh.stdout:
        print("stdout:")
        delta = diff(tcsh.stdout.split(), mysh.stdout.split(), "tcsh", "42sh")
        for line in delta:
            print(line, end="")
        print()
    if tcsh.stderr != mysh.stderr:
        print("stderr:")
        delta = diff(tcsh.stderr.split(), mysh.stderr.split(), "tcsh", "42sh")
        for line in delta:
            print(line, end="")
        print()


def run_test(test, isDebug: bool, isFullLog: bool, hasColor: bool) -> bool:
    mysh = run_command(test["command"], "./42sh")
    tcsh = run_command(test["command"], "tcsh")
    name = test["name"]

    if (tcsh.stdout != mysh.stdout) or (tcsh.stderr != mysh.stderr):
        if isDebug:
            disp_err(tcsh, mysh)
        print(colored(f'Test "{name}" failed.', "red") if hasColor else f'Test "{name}" failed.')
        return (False)
    if isFullLog:
        print(colored(f'Test "{name}" passed.', "green") if hasColor else f'Test "{name}" passed.')
    return (True)


if __name__ == "__main__":
    nb_passed, nb_failed = 0, 0
    tests = get_tests()
    nb_tests = len(tests)
    isFullLog = (len(argv) == 2 and "a" in argv[1])
    isDebug = (len(argv) == 2 and "d" in argv[1])
    hasColor = (len(argv) == 2 and "c" in argv[1])

    for test in tests:
        hasPassed = run_test(test, isDebug, isFullLog, hasColor)
        nb_passed += 1 if hasPassed else 0
        nb_failed += 1 if not hasPassed else 0
    print(f"Ran {nb_tests} tests ({nb_passed} passed and {nb_failed} failed).")
    exit(nb_tests - nb_passed)
