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
int minishell(char **env);
void shell_heartbeat(varenv_t **env, minishell_t *shell);

// Command handling
int check_directory(char *path);
void handle_input(char *input, varenv_t **env, minishell_t *shell);
void handle_errors(int status);
void execute_commands(command_t *commands, varenv_t **env, minishell_t *shell);
void execute_forked(command_t *command, varenv_t **env);
char *find_command(varenv_t *env, char *bin);
char *get_next_argument(char *str, int index);
bool is_command_empty(command_t *command);

// Command linked lists
void list_append(command_t **list, command_t *node);
void list_free(command_t *list);
void free_command(command_t *command);

// PID lists
void pidlist_append(pidlist_t **list, pidlist_t *node);
void pidlist_free(pidlist_t *list);
int pidlist_size(pidlist_t *list);
pidlist_t *create_pidlist(pid_t pid);

// Directories
void handle_cd(varenv_t **env, char *path);
void change_dir(char *dir);
void handle_prev(varenv_t **env, char *path);
void handle_home(varenv_t **env, char *path);
void change_home(varenv_t **env);
void s_handle_cd(varenv_t **env, char *path, minishell_t *shell, \
char *current);
void s_change_dir(varenv_t **env, minishell_t *shell, char *dir, \
char *current);
void s_handle_prev(varenv_t **env, char *path, minishell_t *shell, \
char *current);
void s_handle_home(varenv_t **env, char *path, minishell_t *shell, \
char *current);
void s_change_home(varenv_t **env, minishell_t *shell, \
char *current);

// Signals
void handle_quit(int sig);
void init_signals(void);
