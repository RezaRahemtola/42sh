/*
** EPITECH PROJECT, 2022
** 42sh
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

typedef struct shell_s {
    bool exit;
    int ret;
} shell_t;

typedef struct command_s {
    separator_in_t separator_in;
    separator_out_t separator_out;
    state_t state;
    pid_t pid;
    int ret;
    int fd_in;
    int fd_out;
    char *info_in;
    char *info_out;
    char *input;
    char *path;
    char * const *args;
    struct command_s *prev;
    struct command_s *next;
} command_t;

typedef struct environment {
    char *key;
    char *value;
    struct environment *next;
} env_t;

typedef struct redirection_s {
    char *type;
    bool (*check)(command_t *cmd, char **array, size_t index, env_t *env);
} redirection_t;

typedef struct builtin_s {
    char *command;
    void (*function)(env_t **env, char * const *args);
    int (*silent)(env_t **env, char * const *args, shell_t *shell);
} builtin_t;
