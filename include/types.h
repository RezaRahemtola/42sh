/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Types header
*/

#pragma once

#include <stdbool.h>
#include <sys/wait.h>
#include "my_list.h"

typedef enum separator_in_type {
    NO_IN,
    PIPE_IN,
    FILE_READ,
    INPUT_READ
} separator_in_type_t;

typedef enum separator_out_type {
    NO_OUT,
    PIPE_OUT,
    FILE_WRITE,
    FILE_APPEND,
} separator_out_type_t;

typedef enum separator_next_type {
    NO_NEXT,
    SEMICOLON,
    AND,
    OR
} separator_next_type_t;

typedef enum state {
    IDLE,
    RUNNING,
    IGNORED
} state_t;

typedef struct history {
    size_t index;
    char *command;
    char *time;
} history_t;

typedef struct environment {
    char *key;
    char *value;
    struct environment *next;
} env_t;

typedef struct shell {
    bool exit;
    int ret;
    list_t *history;
    env_t *aliases;
} shell_t;

typedef struct command {
    separator_in_type_t separator_in;
    separator_out_type_t separator_out;
    separator_next_type_t separator_next;
    state_t state;
    pid_t pid;
    int ret;
    int fd_in;
    int fd_out;
    char *info_in;
    char *info_out;
    char *input;
    char *path;
    char *const *args;
    struct command *prev;
    struct command *next;
} command_t;

typedef bool redirection_checker_t(command_t *cmd, char *const *array,
    const env_t *env);
typedef void redirection_function_t(env_t **env, char *const *args, \
    shell_t *shell);
typedef int redirection_silent_function_t(env_t **env, char *const *args,
    shell_t *shell);

typedef struct redirection {
    char *type;
    redirection_checker_t *checker;
} redirection_t;

typedef struct logical {
    char *type;
    separator_next_type_t separator;
} logical_t;

typedef struct builtin {
    char *command;
    redirection_function_t *function;
    redirection_silent_function_t *silent_function;
} builtin_t;
