/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Builtin header
*/

#pragma once

#include "types.h"

void builtin_cd(environment_t **env, char * const *args);
void builtin_env(environment_t **env, char * const *args);
void builtin_exit(environment_t **env, char * const *args);
void builtin_setenv(environment_t **env, char * const *args);
void builtin_unsetenv(environment_t **env, char * const *args);

int silent_cd(environment_t **env, char * const *args, shell_t *shell);
int silent_env(environment_t **env, char * const *args, shell_t *shell);
int silent_exit(environment_t **env, char * const *args, shell_t *shell);
int silent_setenv(environment_t **env, char * const *args, shell_t *shell);
int silent_unsetenv(environment_t **env, char * const *args, shell_t *shell);

bool is_builtin(const char *command);

static const builtin_t BUILTIN[6] = {
        { "exit", &builtin_exit, &silent_exit },
        { "env", &builtin_env, &silent_env },
        { "setenv", &builtin_setenv, &silent_setenv },
        { "unsetenv", &builtin_unsetenv, &silent_unsetenv },
        { "cd", &builtin_cd, &silent_cd },
        { 0, 0, 0 }
};
