import re


def line_break_end_of_file(filename: str, content: str) -> list:
    name = "A3: Line break at the end of file"
    line = content.count('\n') + 1

    if not content.endswith('\n'):
        return [{"type": "info", "file": filename, "line": line, "name": name}]
    return []

def function_separation(filename: str, content: str) -> list:
    name = "G2: Separation of functions"

    if len(re.findall("}\n{3,}", content)) > 0:
        line: int = content.split("\n\n\n")[0].count('\n') + 2
        return [{"type": "minor", "file": filename, "line": line, "name": name}]
    return []

def leading_line(filename: str, content: str) -> list:
    name = "G9 - Leading/Trailing lines"
    line = []
    if content.startswith('\n'):
        line.append({"type": "minor", "file": filename, "line": 1, "name": name})
    if content.endswith('\n\n'):
        line.append({"type": "minor", "file": filename, "line": content.count('\n'), "name": name})
    return line

