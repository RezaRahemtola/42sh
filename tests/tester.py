#!/usr/bin/env python
from json import load as load_json
from subprocess import run
from sys import argv
from termcolor import colored
from os import path


def get_json_data(filepath: str) -> None:
    with open(filepath) as json_file:
        return load_json(json_file)


def run_command(command: str, piped_path: str) -> None:
    return run(f'echo "{command}" | {piped_path}', shell=True, capture_output=True, text=True)


def run_test(debug: bool, disp_all: bool, color: bool) -> None:
    mysh = run_command(test["command"], "./42sh")
    tcsh = run_command(test["command"], "tcsh")
    name = test["name"]

    if (tcsh.stdout not in mysh.stdout) or (tcsh.stderr not in mysh.stderr):
        if debug:
            print(f"TCSH_out:{tcsh.stdout}\n42sh_out:{mysh.stdout}")
            print(f"TCSH_err:{tcsh.stderr}\n42sh_err:{mysh.stderr}")
        print(colored(f'Test "{name}" failed.', "red") if color else f'Test "{name}" failed.')
        return (-1)
    else:
        if disp_all:
            print(colored(f'Test "{name}" passed.', "green") if color else f'Test "{name}" passed.')
        return (1)


if __name__ == "__main__":
    nb_passed = 0
    nb_failed = 0
    current_path = path.dirname(path.realpath(__file__))
    json_data = get_json_data(current_path + "/config.json")
    nb_tests = len(json_data["tests"])
    disp_all = True if (len(argv) == 2 and "a" in argv[1]) else False
    debug = True if (len(argv) == 2 and "d" in argv[1]) else False
    color = (len(argv) == 2 and "c" in argv[1])

    for test in json_data["tests"]:
        result = run_test(debug, disp_all, color)
        nb_passed += 1 if result == 1 else 0
        nb_failed += 1 if result == -1 else 0
    print(f"Ran {nb_tests} tests ({nb_passed} passed and {nb_failed} failed).")
    exit(nb_tests - nb_passed)
