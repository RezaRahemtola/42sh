/*
** EPITECH PROJECT, 2021
** minishell2
** File description:
** Header
*/

#pragma once

#include "types.h"

static const int EXIT_USAGE = 84;

// Core
int start_minishell(char **env);
void do_heartbeat(varenv_t **env, minishell_t *shell);

// Command handling
bool is_directory(const char *path);
void handle_input(const char *input, varenv_t **env, minishell_t *shell);
void handle_errors(int status);
void execute_commands(command_t *commands, varenv_t **env, minishell_t *shell);
void execute_forked(command_t *command, varenv_t **env);
char *find_command(varenv_t *env, const char *bin);
char *get_next_argument(const char *str, size_t index);
bool is_command_empty(command_t *command);

// Command linked lists
void list_append(command_t **list, command_t *node);
void list_free(command_t *list);
void free_command(command_t *command);

// Directories
void handle_cd(varenv_t **env, const char *path);
void change_current_path(const char *dir);
void handle_prev(varenv_t **env, const char *path);
void handle_home(varenv_t **env, const char *path);
void change_home(varenv_t **env);
int handle_cd_silently(varenv_t **env, const char *path, const char *current);
int change_dir_silently(varenv_t **env, const char *dir, const char *current);
int handle_prev_silently(varenv_t **env, const char *path, const char *current);
int handle_home_silently(varenv_t **env, const char *path, const char *current);
int change_home_silently(varenv_t **env, const char *current);

// Signals
void handle_quit(int sig);
void init_signals(void);
