#!/usr/bin/env python
import subprocess
import json
from sys import argv
from termcolor import colored
from os import path

def get_json_data(filepath: str):
    with open(filepath) as json_file:
        return json.load(json_file)

def run_command(command: str, piped_path: str):
    return subprocess.run(f'echo "{command}" | {piped_path}', shell=True, capture_output=True, text=True)

if __name__ == "__main__":
    failed = 0
    passed = 0
    current_path = path.dirname(path.realpath(__file__))
    json_data = get_json_data(current_path + "/config.json")
    disp_all = True if (len(argv) == 2 and "a" in argv[1]) else False
    debug = True if (len(argv) == 2 and "d" in argv[1]) else False

    for test in json_data["tests"]:
        mysh = run_command(test["command"], "./mysh")
        tcsh = run_command(test["command"], "tcsh")
        name = test["name"]
        if (tcsh.stdout not in mysh.stdout) or (tcsh.stderr not in mysh.stderr):
            if debug:
                print(f"TCSH_out:{tcsh.stdout}\nMYSH_out:{mysh.stdout}")
                print(f"TCSH_err:{tcsh.stderr}\nMYSH_err:{mysh.stderr}")
            failed += 1
            print(colored(f'Test "{name}" failed.', "red"))
        else:
            passed += 1
            if disp_all:
                print(colored(f'Test "{name}" passed.', "green"))
    print(f"Ran {failed + passed} tests ({passed} passed and {failed} failed).")
    exit(failed)
