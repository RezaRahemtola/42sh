#!/usr/bin/env python
from json import load as load_json
from subprocess import run
from sys import argv
from termcolor import colored
from os import path


def get_json_data(filepath: str):
    with open(filepath) as json_file:
        return load_json(json_file)


def run_command(command: str, piped_path: str):
    return run(f'echo "{command}" | {piped_path}', shell=True, capture_output=True, text=True)


def disp_err(tcsh, mysh) -> None:
    if tcsh.stdout not in mysh.stdout:
        print(f"TCSH_out:{tcsh.stdout}\n42sh_out:{mysh.stdout}")
    if tcsh.stderr not in mysh.stderr:
        print(f"TCSH_err:{tcsh.stderr}\n42sh_err:{mysh.stderr}")


def run_test(isDebug: bool, isFullLog: bool, hasColor: bool) -> bool:
    mysh = run_command(test["command"], "./42sh")
    tcsh = run_command(test["command"], "tcsh")
    name = test["name"]

    if (tcsh.stdout not in mysh.stdout) or (tcsh.stderr not in mysh.stderr):
        if isDebug:
            disp_err(tcsh, mysh)
        print(colored(f'Test "{name}" failed.', "red") if hasColor else f'Test "{name}" failed.')
        return (False)
    else:
        if isFullLog:
            print(colored(f'Test "{name}" passed.', "green") if hasColor else f'Test "{name}" passed.')
        return (True)


if __name__ == "__main__":
    nb_passed = 0
    nb_failed = 0
    current_path = path.dirname(path.realpath(__file__))
    json_data = get_json_data(current_path + "/config.json")
    nb_tests = len(json_data["tests"])
    isFullLog = True if (len(argv) == 2 and "a" in argv[1]) else False
    isDebug = True if (len(argv) == 2 and "d" in argv[1]) else False
    hasColor = (len(argv) == 2 and "c" in argv[1])

    for test in json_data["tests"]:
        hasPassed = run_test(isDebug, isFullLog, hasColor)
        nb_passed += 1 if hasPassed else 0
        nb_failed += 1 if not hasPassed else 0
    print(f"Ran {nb_tests} tests ({nb_passed} passed and {nb_failed} failed).")
    exit(nb_tests - nb_passed)
