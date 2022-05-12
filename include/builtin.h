/*
** EPITECH PROJECT, 2022
** minishell2
** File description:
** Builtin header
*/

#pragma once

#include "types.h"

void builtin_cd(varenv_t **env, char * const *args);
void builtin_env(varenv_t **env, char * const *args);
void builtin_exit(varenv_t **env, char * const *args);
void builtin_setenv(varenv_t **env, char * const *args);
void builtin_unsetenv(varenv_t **env, char * const *args);

int silent_cd(varenv_t **env, char * const *args, minishell_t *shell);
int silent_env(varenv_t **env, char * const *args, minishell_t *shell);
int silent_exit(varenv_t **env, char * const *args, minishell_t *shell);
int silent_setenv(varenv_t **env, char * const *args, minishell_t *shell);
int silent_unsetenv(varenv_t **env, char * const *args, minishell_t *shell);

bool is_builtin(const char *command);

static const builtin_t BUILTIN[6] = {
        { "exit", &builtin_exit, &silent_exit },
        { "env", &builtin_env, &silent_env },
        { "setenv", &builtin_setenv, &silent_setenv },
        { "unsetenv", &builtin_unsetenv, &silent_unsetenv },
        { "cd", &builtin_cd, &silent_cd },
        { 0, 0, 0 }
};
