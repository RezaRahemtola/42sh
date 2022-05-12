/*
** EPITECH PROJECT, 2022
** minishell2
** File description:
** Output redirection checks
*/

#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include "messages.h"
#include "my_string.h"
#include "my_arrays.h"
#include "redirections.h"

static bool check_null_ambiguous(command_t *command, char **array, size_t index)
{
    if (array[index + 1] == NULL || strlen(array[index + 1]) == 0) {
        fprintf(stderr, "%s\n", MISSING_NAME);
        return (false);
    }
    if (command->separator_out != NO_OUT) {
        fprintf(stderr, "%s\n", AMBIGUOUS_OUTPUT);
        return (false);
    }
    return (true);
}

bool check_out_append(command_t *cmd, char **array, size_t index,
    environment_t *env)
{
    char **sub = NULL;

    if (!check_null_ambiguous(cmd, array, index))
        return (false);
    cmd->separator_out = FILE_APPEND;
    sub = my_strsplit_many(array[index + 1], " \t");
    if (sub == NULL)
        return (false);
    if (sub[0] == NULL || strlen(sub[0]) == 0) {
        fprintf(stderr, "%s\n", MISSING_NAME);
        my_free_arrays(1, sub);
        return (false);
    }
    cmd->info_out = strdup(sub[0]);
    replace_args(cmd, array[index], array[index + 1], env);
    my_free_arrays(1, sub);
    return (true);
}

bool check_out_write(command_t *cmd, char **array, size_t index,
    environment_t *env)
{
    char **sub = NULL;

    if (!check_null_ambiguous(cmd, array, index))
        return (false);
    cmd->separator_out = FILE_WRITE;
    sub = my_strsplit_many(array[index + 1], " \t");
    if (sub == NULL)
        return (false);
    if (sub[0] == NULL || strlen(sub[0]) == 0) {
        fprintf(stderr, "%s\n", MISSING_NAME);
        my_free_arrays(1, sub);
        return (false);
    }
    cmd->info_out = strdup(sub[0]);
    replace_args(cmd, array[index], array[index + 1], env);
    my_free_arrays(1, sub);
    return (true);
}
