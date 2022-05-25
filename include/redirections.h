/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Redirections array
*/

#pragma once

#include "types.h"

bool check_out_append(command_t *cmd, char *const *array, const env_t *env);
bool check_out_write(command_t *cmd, char *const *array, const env_t *env);
bool check_in_file(command_t *cmd, char *const *array, const env_t *env);
bool check_in_input(command_t *cmd, char *const *array, const env_t *env);

// Input and output
bool open_input_redirection(command_t *command);
bool open_output_redirection(command_t *command);
void close_redirections(const command_t *command);

// Pipes
bool open_pipe_redirections(command_t *command);
void handle_pipe_redirections(const command_t *command);

// Utils
bool check_redirections(command_t *list, shell_t *shell);
redirection_t get_redirection(const char *str, size_t index);
char **split_redirections(const char *input);

void replace_args(command_t *cmd, const char *redir, const char *str,
    const env_t *env);

bool is_valid_redirection(const command_t *cmd, char *const *array,
    bool is_input);

static const redirection_t REDIRECTIONS[5] = {
        { ">>", &check_out_append },
        { ">", &check_out_write },
        { "<<", &check_in_input },
        { "<", &check_in_file },
        {0, 0}
};
