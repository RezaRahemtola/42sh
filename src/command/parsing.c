/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Command parsing
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "builtin.h"
#include "logical.h"
#include "messages.h"
#include "my_arrays.h"
#include "my_string.h"
#include "my.h"
#include "redirections.h"
#include "shell.h"

static bool init_command(command_t *cmd, const env_t *env, const char *input)
{
    cmd->separator_in = NO_IN;
    cmd->separator_out = NO_OUT;
    cmd->separator_next = NO_NEXT;
    cmd->state = IDLE;
    cmd->pid = 0;
    cmd->ret = -1;
    cmd->fd_in = 0;
    cmd->fd_out = 0;
    cmd->info_in = NULL;
    cmd->info_out = NULL;
    cmd->input = strdup(input);
    cmd->args = my_strsplit_many(input, " \t");
    if (cmd->args == NULL) {
        my_free(2, cmd->input, cmd);
        return (false);
    }
    cmd->path = find_command(env, cmd->args[0]);
    cmd->prev = NULL;
    cmd->next = NULL;
    return (true);
}

static command_t *get_command(command_t **list, const env_t *env,
const char *str, size_t i)
{
    command_t *command = malloc(sizeof(command_t));

    if (command == NULL || !init_command(command, env, str))
        return (NULL);
    list_append(list, command);
    if (i > 0) {
        if (is_command_empty(command) || is_command_empty(command->prev)) {
            fprintf(stderr, "%s\n", MISSING_COMMAND);
            return (NULL);
        }
        command->prev->separator_out = PIPE_OUT;
        command->separator_in = PIPE_IN;
    }
    return (command);
}

static bool parse_command(command_t **list, const env_t *env, const char *input,
const char *separator)
{
    int size = strlen(input);
    char **array = my_strsplit(input, '|');
    command_t *command = NULL;

    if (array == NULL)
        return (false);
    if (input[MAX(0, size - 1)] == '|' || input[0] == '|') {
        fprintf(stderr, "%s\n", MISSING_COMMAND);
        my_free_arrays(1, array);
        return (false);
    }
    for (size_t i = 0; array[i] != NULL; i++) {
        command = get_command(list, env, array[i], i);
        if (command == NULL)
            break;
        if (array[i + 1] == NULL && separator != NULL)
            apply_logical(command, separator);
    }
    my_free_arrays(1, array);
    return (command != NULL);
}

static void pipe_and_exec(command_t *cmd, shell_t *shell)
{
    for (command_t *tmp = cmd; tmp != NULL; tmp = tmp->next)
        tmp->job_check = false;
    if (!check_logicals(cmd, shell))
        return;
    if (!check_redirections(cmd, shell) || !open_pipe_redirections(cmd)) {
        shell->ret = 1;
    } else {
        execute_commands(cmd, shell);
    }
}

void handle_input(const char *input, shell_t *shell)
{
    command_t *list = NULL;
    size_t size = strlen(input);
    char *line = my_substr_size(input, 0, size - 1, size);
    char *const *array = split_logical(line);

    for (size_t i = 0; array[i] != NULL; i++) {
        if (!parse_command(&list, shell->env, array[i], array[i + 1])) {
            free(line);
            my_free_arrays(1, array);
            list_free(list);
            shell->ret = 1;
            return;
        }
        i += (array[i + 1] != NULL);
    }
    pipe_and_exec(list, shell);
    free(line);
    my_free_arrays(1, array);
    list_free(list);
}
