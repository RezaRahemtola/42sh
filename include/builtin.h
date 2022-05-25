/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Builtin header
*/

#pragma once

#include "types.h"

void builtin_cd(env_t **env, char *const *args, shell_t *shell);
void builtin_env(env_t **env, char *const *args, shell_t *shell);
void builtin_exit(env_t **env, char *const *args, shell_t *shell);
void builtin_setenv(env_t **env, char *const *args, shell_t *shell);
void builtin_unsetenv(env_t **env, char *const *args, shell_t *shell);
void builtin_history(env_t **env, char *const *args, shell_t *shell);
void builtin_alias(env_t **env, char *const *args, shell_t *shell);

int silent_cd(env_t **env, char *const *args, shell_t *shell);
int silent_env(env_t **env, char *const *args, shell_t *shell);
int silent_exit(env_t **env, char *const *args, shell_t *shell);
int silent_setenv(env_t **env, char *const *args, shell_t *shell);
int silent_unsetenv(env_t **env, char *const *args, shell_t *shell);
int silent_history(env_t **env, char *const *args, shell_t *shell);
int silent_alias(env_t **env, char *const *args, shell_t *shell);

bool is_builtin(const char *command);

static const builtin_t BUILTIN[8] = {
        { "exit", &builtin_exit, &silent_exit },
        { "env", &builtin_env, &silent_env },
        { "setenv", &builtin_setenv, &silent_setenv },
        { "unsetenv", &builtin_unsetenv, &silent_unsetenv },
        { "cd", &builtin_cd, &silent_cd },
        { "history", &builtin_history, &silent_history },
        { "alias", &builtin_alias, &silent_alias },
        { 0, 0, 0 }
};
