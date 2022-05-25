/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Header
*/

#pragma once

#include "types.h"

static const int EXIT_USAGE = 84;

// Core
int start_shell(const char *const *env);
void do_heartbeat(env_t **env, shell_t *shell);

// Command handling
bool is_directory(const char *path);
void handle_input(const char *input, env_t **env, shell_t *shell);
void handle_errors(int status);
void execute_commands(command_t *commands, env_t **env, shell_t *shell);
void execute_forked(command_t *command, env_t **env, shell_t *shell);
char *find_command(const env_t *env, const char *bin);
char *get_next_argument(const char *str, size_t index);
bool is_command_empty(const command_t *command);

// Command linked lists
void list_append(command_t **list, command_t *node);
void list_free(command_t *list);

// Directories
void handle_cd(env_t **env, const char *path);
void change_current_path(const char *dir);
void handle_home(env_t **env, const char *path);
void change_home(env_t **env);
int handle_cd_silently(env_t **env, const char *path, const char *current);
int change_dir_silently(env_t **env, const char *dir, const char *current);
int handle_home_silently(env_t **env, const char *path, const char *current);
int change_home_silently(env_t **env, const char *current);

// Signals
void handle_quit(int sig);
void init_signals(void);

// Others
void append_end(char **array, const char *input, size_t pattern, size_t index);
