/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Messages header file
*/

#pragma once

typedef const char *const msg_t;

// Overall
static msg_t TOO_FEW_ARGS = "Too few arguments.";
static msg_t TOO_MANY_ARGS = "Too many arguments.";
static msg_t UNKNOWN_COMMAND = "Command not found.";
static msg_t NO_FILE = "No such file or directory.";
static msg_t SYNTAX_ERROR = "Expression Syntax.";
static msg_t NUMBER_ERROR = "Badly formed number.";

// Builtins
static msg_t ALIAS_DANGEROUS = "Too dangerous to alias that.";
static msg_t BEGIN_LETTER = "Variable name must begin with a letter.";
static msg_t NON_ALPHA = "Variable name must contain alphanumeric characters.";
static msg_t READ_ONLY = "is read-only.";
static msg_t CD_USAGE = "Usage: cd [-plvn][-|<dir>].";
static msg_t NO_HOME_VARIABLE = "No $home variable set.";
static msg_t NO_HOME_DIR = "No home directory.";
static msg_t HOME_DIR_ERROR = "Can't change to home directory.";
static msg_t NO_EVENT = "Event not found.";

// Redirections
static msg_t AMBIGUOUS_INPUT = "Ambiguous input redirect.";
static msg_t AMBIGUOUS_OUTPUT = "Ambiguous output redirect.";
static msg_t MISSING_COMMAND = "Invalid null command.";
static msg_t MISSING_NAME = "Missing name for redirect.";

// Error handling
static msg_t FOLDER_ERROR = "Permission denied.";
static msg_t NOT_DIRECTORY = "Not a directory.";
static msg_t WRONG_ARCH = "Exec format error. Wrong Architecture.";
static msg_t FLOATING_POINT = "Floating exception";
static msg_t CORE_DUMPED = " (core dumped)";
static msg_t NO_USER = "Unknown user:";
static msg_t IGNOREEOF_MESSAGE = "Use \"exit\" to leave 42sh.";
