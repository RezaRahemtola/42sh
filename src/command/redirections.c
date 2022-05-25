/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Redirections checker
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "messages.h"
#include "shell.h"
#include "redirections.h"
#include "my_arrays.h"
#include "my_string.h"
#include "my.h"

static bool check_redirection(command_t *command, const env_t *env)
{
    char **array = split_redirections(command->input);
    size_t size = my_arraylen(array);
    redirection_t redir;

    for (size_t i = 0; i < size; i++) {
        redir = get_redirection(array[i], 0);
        if (redir.checker != NULL && !redir.checker(command, &array[i], env)) {
            my_free_arrays(1, array);
            return (false);
        }
    }
    if ((command->args[0] == NULL || strlen(command->args[0]) == 0)) {
        fprintf(stderr, "%s\n", MISSING_COMMAND);
        return (false);
    }
    my_free_arrays(1, array);
    return (true);
}

bool check_redirections(command_t *list, shell_t *shell)
{
    bool empty = false;
    command_t *current = list;

    while (current != NULL) {
        empty = (current->args[0] == NULL || strlen(current->args[0]) == 0);
        if (!empty && !check_redirection(current, shell->env)) {
            shell->ret = 1;
            return (false);
        }
        current = current->next;
    }
    return (true);
}

static char *get_redirect_argument_sum(const char *str, const char *redirect,
    const char *input)
{
    char *target = get_next_argument(str, 0);
    size_t total_len;
    char *sum = NULL;
    char *rep = NULL;

    if (target == NULL)
        return (NULL);
    total_len = strlen(redirect) + strlen(target) + 1;
    sum = malloc(sizeof(char) * (total_len));
    sprintf(sum, "%s%s", redirect, target);
    if (sum == NULL) {
        free(target);
        return (NULL);
    }
    rep = my_strrep(input, sum, "");
    my_free(2, sum, target);
    return (rep);
}

void replace_args(command_t *command, const char *redir, const char *str,
    const env_t *env)
{
    char *rep = get_redirect_argument_sum(str, redir, command->input);

    if (rep == NULL)
        return;
    my_free(2, command->input, command->path);
    my_free_arrays(1, command->args);
    command->input = rep;
    command->args = my_strsplit_many(command->input, " \t");
    command->path = find_command(env, command->args[0]);
}
