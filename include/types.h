/*
** EPITECH PROJECT, 2022
** minishell2
** File description:
** Types header
*/

#pragma once

#include <stdbool.h>
#include <sys/wait.h>

typedef enum separator_in_e {
    NO_IN,
    PIPE_IN,
    FILE_READ,
    INPUT_READ
} separator_in_t;

typedef enum separator_out_e {
    NO_OUT,
    PIPE_OUT,
    FILE_WRITE,
    FILE_APPEND,
} separator_out_t;

typedef enum state_e {
    IDLE,
    RUNNING,
    IGNORED
} state_t;

typedef struct minishell_s {
    int exit;
    int ret;
} minishell_t;

typedef struct command_s {
    separator_in_t separator_in;
    separator_out_t separator_out;
    state_t state;
    pid_t pid;
    int fd_in;
    int fd_out;
    char *info_in;
    char *info_out;
    char *input;
    char *path;
    char **args;
    struct command_s *prev;
    struct command_s *next;
} command_t;

typedef struct varenv_s {
    char *key;
    char *value;
    struct varenv_s *next;
} varenv_t;

typedef struct redirection_s {
    char *type;
    bool (*check)(command_t *command, char **array, int index, varenv_t *env);
} redirection_t;

typedef struct builtin_s {
    char *command;
    void (*function)(varenv_t **env, char **args);
    void (*silent)(varenv_t **env, char **args, minishell_t *shell);
} builtin_t;
