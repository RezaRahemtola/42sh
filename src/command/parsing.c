/*
** EPITECH PROJECT, 2022
** minishell2
** File description:
** Command parsing
*/

#include <stdlib.h>
#include <string.h>
#include "messages.h"
#include "minishell.h"
#include "my_string.h"
#include "my.h"
#include "redirections.h"

static bool init_command(command_t *command, varenv_t *env, char *input)
{
    command->separator_in = NO_IN;
    command->separator_out = NO_OUT;
    command->state = IDLE;
    command->fd_in = 0;
    command->fd_out = 0;
    command->info_in = NULL;
    command->info_out = NULL;
    command->input = my_strdup(input);
    command->args = my_strsplit_many(input, " \t");
    if (command->args == NULL) {
        my_free(2, command->input, command);
        return (false);
    }
    command->path = find_command(env, command->args[0]);
    command->prev = NULL;
    command->next = NULL;
    return (true);
}

static bool is_command_valid(command_t **list, varenv_t *env, char *str, int i)
{
    command_t *command = malloc(sizeof(command_t));

    if (command == NULL || !init_command(command, env, str)) {
        return (false);
    }
    list_append(list, command);
    if (i > 0) {
        if (is_command_empty(command) || is_command_empty(command->prev)) {
            my_dprintf(2, "%s\n", MISSING_COMMAND);
            return (false);
        }
        command->prev->separator_out = PIPE_OUT;
        command->separator_in = PIPE_IN;
    }
    return (true);
}

static bool parse_command(command_t **list, varenv_t *env, char *input)
{
    int size = strlen(input);
    char **array = my_strsplit(input, '|');

    if (array == NULL) {
        return (false);
    } else if (input[size - 1] == '|' || input[0] == '|') {
        my_dprintf(2, "%s\n", MISSING_COMMAND);
        my_free_arrays(1, array);
        return (false);
    }
    for (int i = 0; array[i] != NULL; i++) {
        if (!is_command_valid(list, env, array[i], i)) {
            my_free_arrays(1, array);
            return (false);
        }
    }
    my_free_arrays(1, array);
    return (true);
}

static void pipe_and_exec(command_t *cmd, varenv_t **env, minishell_t *shell)
{
    if (!check_redirections(cmd, shell, *env)) {
        shell->ret = 1;
        return;
    }
    if (!open_pipe_redirections(cmd)) {
        shell->ret = 1;
        return;
    }
    execute_commands(cmd, env, shell);
}

void handle_input(char *input, varenv_t **env, minishell_t *shell)
{
    command_t *list = NULL;
    int size = strlen(input);
    char *line = my_substr_size(input, 0, size - 1, size);
    char **array = my_strsplit(line, ';');

    for (int i = 0; array[i] != NULL; i++) {
        if (!parse_command(&list, *env, array[i])) {
            free(line);
            my_free_arrays(1, array);
            list_free(list);
            shell->ret = 1;
            return;
        }
    }
    pipe_and_exec(list, env, shell);
    free(line);
    my_free_arrays(1, array);
    list_free(list);
}
