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
int start_shell(char **env);
void do_heartbeat(environment_t **env, shell_t *shell);

// Command handling
bool is_directory(const char *path);
void handle_input(const char *input, environment_t **env, shell_t *shell);
void handle_errors(int status);
void execute_commands(command_t *commands, environment_t **env, shell_t *shell);
void execute_forked(command_t *command, environment_t **env);
char *find_command(environment_t *env, const char *bin);
char *get_next_argument(const char *str, size_t index);
bool is_command_empty(command_t *command);

// Command linked lists
void list_append(command_t **list, command_t *node);
void list_free(command_t *list);
void free_command(command_t *command);

// Directories
void handle_cd(environment_t **env, const char *path);
void change_current_path(const char *dir);
void handle_prev(environment_t **env, const char *path);
void handle_home(environment_t **env, const char *path);
void change_home(environment_t **env);
int handle_cd_silently(environment_t **env, const char *path, const char *current);
int change_dir_silently(environment_t **env, const char *dir, const char *current);
int handle_prev_silently(environment_t **env, const char *path, const char *current);
int handle_home_silently(environment_t **env, const char *path, const char *current);
int change_home_silently(environment_t **env, const char *current);

// Signals
void handle_quit(int sig);
void init_signals(void);
