/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Builtin header
*/

#pragma once

#include "types.h"

void builtin_fg(env_t **env, char *const *args);
void builtin_cd(env_t **env, char *const *args);
void builtin_env(env_t **env, char *const *args);
void builtin_exit(env_t **env, char *const *args);
void builtin_setenv(env_t **env, char *const *args);
void builtin_unsetenv(env_t **env, char *const *args);
void builtin_jobs(env_t **env, char *const *args);

int silent_cd(env_t **env, char *const *args, shell_t *shell);
int silent_fg(env_t **env, char *const *args, shell_t *shell);
int silent_job(env_t **env, char *const *args, shell_t *shell);
int silent_env(env_t **env, char *const *args, shell_t *shell);
int silent_exit(env_t **env, char *const *args, shell_t *shell);
int silent_setenv(env_t **env, char *const *args, shell_t *shell);
int silent_unsetenv(env_t **env, char *const *args, shell_t *shell);

bool is_builtin(const char *command);

static const builtin_t BUILTIN[8] = {
        { "exit", &builtin_exit, &silent_exit },
        { "env", &builtin_env, &silent_env },
        { "setenv", &builtin_setenv, &silent_setenv },
        { "unsetenv", &builtin_unsetenv, &silent_unsetenv },
        { "cd", &builtin_cd, &silent_cd },
        { "jobs", &builtin_jobs, &silent_job },
        { "fg", &builtin_fg, &silent_fg },
        { 0, 0, 0 }
};
