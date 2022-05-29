/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Builtin header
*/

#pragma once

#include "types.h"

void builtin_cd(shell_t *shell, char *const *args);
void builtin_env(shell_t *shell, char *const *args);
void builtin_exit(shell_t *shell, char *const *args);
void builtin_setenv(shell_t *shell, char *const *args);
void builtin_unsetenv(shell_t *shell, char *const *args);
void builtin_set(shell_t *shell, char *const *args);
void builtin_unset(shell_t *shell, char *const *args);
void builtin_history(shell_t *shell, char *const *args);
void builtin_alias(shell_t *shell, char *const *args);
void builtin_unalias(shell_t *shell, char *const *args);
void builtin_jobs(shell_t *shell, char *const *args);
void builtin_fg(shell_t *shell, char *const *args);

int silent_cd(shell_t *shell, char *const *args);
int silent_env(shell_t *shell, char *const *args);
int silent_exit(shell_t *shell, char *const *args);
int silent_setenv(shell_t *shell, char *const *args);
int silent_unsetenv(shell_t *shell, char *const *args);
int silent_set(shell_t *shell, char *const *args);
int silent_unset(shell_t *shell, char *const *args);
int silent_history(shell_t *shell, char *const *args);
int silent_alias(shell_t *shell, char *const *args);
int silent_unalias(shell_t *shell, char *const *args);
int silent_jobs(shell_t *shell, char *const *args);
int silent_fg(shell_t *shell, char *const *args);

bool is_builtin(const char *command);

void replace_aliases(command_t *commands, env_t *aliases, env_t *env);
void replace_variables(command_t *command, shell_t *shell);
bool replace_home(command_t *command, shell_t *shell, size_t size);
bool replace_var(command_t *command, shell_t *shell, size_t index, size_t i);
void replace_test(command_t *command, shell_t *shell, size_t index, size_t i);
void replace_argument(command_t *command, size_t index, char *new_arg);

char *get_variable_name(const char *str, size_t start, size_t len);
char *env_value(const shell_t *shell, const char *name);

static const builtin_t BUILTIN[13] = {
        { "exit", &builtin_exit, &silent_exit },
        { "env", &builtin_env, &silent_env },
        { "setenv", &builtin_setenv, &silent_setenv },
        { "unsetenv", &builtin_unsetenv, &silent_unsetenv },
        { "set", &builtin_set, &silent_set },
        { "unset", &builtin_unset, &silent_unset },
        { "cd", &builtin_cd, &silent_cd },
        { "history", &builtin_history, &silent_history },
        { "alias", &builtin_alias, &silent_alias },
        { "unalias", &builtin_unalias, &silent_unalias },
        { "jobs", &builtin_jobs, &silent_job },
        { "fg", &builtin_fg, &silent_fg },
        { 0, 0, 0 }
};
