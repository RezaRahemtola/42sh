/*
** EPITECH PROJECT, 2022
** minishell2
** File description:
** Redirections array
*/

#pragma once

#include <stddef.h>
#include "types.h"

bool check_out_append(command_t *cmd, char **arr, size_t index, varenv_t *env);
bool check_out_write(command_t *cmd, char **arr, size_t index, varenv_t *env);
bool check_in_file(command_t *cmd, char **arr, size_t index, varenv_t *env);
bool check_in_input(command_t *cmd, char **arr, size_t index, varenv_t *env);

// Input and output
bool open_input_redirection(command_t *command);
bool open_output_redirection(command_t *command);
void close_input_redirection(command_t *command);
void close_output_redirection(command_t *command);

// Pipes
bool open_pipe_redirections(command_t *command);
void handle_pipe_redirections(command_t *command);

bool check_redirections(command_t *list, minishell_t *shell, varenv_t *env);
redirection_t get_redirection(const char *str, size_t index);
char **split_redirections(const char *input);

void replace_args(command_t *cmd, const char *redir, const char *str,
varenv_t *env);

static const redirection_t REDIRECTIONS[5] = {
        { ">>", &check_out_append },
        { ">", &check_out_write },
        { "<<", &check_in_input },
        { "<", &check_in_file },
        { 0, 0}
};
