/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Header
*/

#pragma once

#include "types.h"

static const int EXIT_USAGE = 84;

// Core
int start_shell(const char *const *env);
void do_heartbeat(shell_t *shell, const char *const *env);
void load_rc(shell_t *shell);

// Command handling
bool is_directory(const char *path);
void handle_input(const char *input, shell_t *shell);
void handle_errors(int status);
void execute_commands(command_t *commands, shell_t *shell);
void execute_forked(command_t *command, shell_t *shell);
void execute_line(const char *line, shell_t *shell);
void exec_special_alias(const char *key, shell_t *shell);
char *find_command(const env_t *env, const char *bin);
char *get_next_argument(const char *str, size_t index);
bool is_command_empty(const command_t *command);
char *join_array(char *const *array, size_t start, size_t end);

// Command linked lists
void list_append(command_t **list, command_t *node);
size_t list_size(command_t *list);
void list_free(command_t *list);

// Directories
void handle_cd(const env_t *env, const char *path);
void change_current_path(const char *dir);
void change_home(const env_t *env, const localenv_t *localenv);
int handle_cd_silently(shell_t *shell, const char *path, const char *current);
int change_dir_silently(shell_t *shell, const char *dir, const char *current);
int change_home_silently(shell_t *shell, const char *current);

// Status handling
bool must_relay_status(command_t *command);

// Signals
void handle_quit(int sig);
void init_signals(void);

// Prompt
void prompt(shell_t *shell);

// Others
void append_end(char **array, const char *input, size_t pattern, size_t index);
