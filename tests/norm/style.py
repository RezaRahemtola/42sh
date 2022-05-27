#!/usr/bin/env python
import re
import checks
from json import load as loadJSON
from sys import argv
from glob import glob
from termcolor import colored
from os import path


def get_json_data(filepath: str) -> dict:
    with open(filepath) as json_file:
        return loadJSON(json_file)

def run_regex(filename: str, json_data: dict) -> list:
    file = open(filename, 'r')
    content = file.read()
    found = []

    for index, line in enumerate(content.split('\n')):
        for rule in json_data["norm"]:
            if len(re.findall(rule["regex"], line)) > 0:
                found.append({"type": rule["type"], "file": filename, "line": index + 1, "name": rule["name"]})
    file.close()
    return found

def run_functions(filename: str) -> list:
    file = open(filename, 'r')
    content = file.read()
    found = []
    functions = [getattr(checks, elem) for elem in dir(checks) if callable(getattr(checks, elem))]

    for function in functions:
        found += function(filename, content)
    return found

def display_output(found: list) -> None:
    major = len([elem for elem in found if elem["type"] == "major"])
    minor = len([elem for elem in found if elem["type"] == "minor"])
    info = len([elem for elem in found if elem["type"] == "info"])

    for error in found:
        if error["type"] == "major":
            color = "red"
        elif error["type"] == "minor":
            color = "yellow"
        else:
            color = "green"
        print(f"{colored(error['name'] + ' detected in', color)} {colored(error['file'] + ':' + str(error['line']), 'blue')}")
    print(f"\nTotal of {len(found)} coding style errors found ({colored(major, 'red')} major, {colored(minor, 'yellow')} minor and {colored(info, 'green')} info).")

if __name__ == "__main__":
    current_path = path.dirname(path.realpath(__file__))
    json_data = get_json_data(current_path + "/config.json")
    found = []

    for folder in argv[1:]:
        for filename in glob(folder + '/**/*.c', recursive=True):
            found += run_regex(filename, json_data)
            found += run_functions(filename)
    display_output(found)
    exit(len(found))

