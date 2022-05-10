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

static bool check_null_ambiguous(command_t *command, char **array, int index)
{
    if (array[index + 1] == NULL || strlen(array[index + 1]) == 0) {
        fprintf(stderr, "%s\n", MISSING_NAME);
        return (false);
    } else if (command->separator_out != NO_OUT) {
        fprintf(stderr, "%s\n", AMBIGUOUS_OUTPUT);
        return (false);
    }
    return (true);
}

bool check_out_append(command_t *command, char **array, int index, \
varenv_t *env)
{
    char **sub = NULL;

    if (!check_null_ambiguous(command, array, index)) {
        return (false);
    }
    command->separator_out = FILE_APPEND;
    sub = my_strsplit_many(array[index + 1], " \t");
    if (sub == NULL) {
        return (false);
    } else if (sub[0] == NULL || strlen(sub[0]) == 0) {
        fprintf(stderr, "%s\n", MISSING_NAME);
        my_free_arrays(1, sub);
        return (false);
    }
    command->info_out = strdup(sub[0]);
    replace_args(command, array[index], array[index + 1], env);
    my_free_arrays(1, sub);
    return (true);
}

bool check_out_write(command_t *command, char **array, int index, \
varenv_t *env)
{
    char **sub = NULL;

    if (!check_null_ambiguous(command, array, index)) {
        return (false);
    }
    command->separator_out = FILE_WRITE;
    sub = my_strsplit_many(array[index + 1], " \t");
    if (sub == NULL) {
        return (false);
    } else if (sub[0] == NULL || strlen(sub[0]) == 0) {
        fprintf(stderr, "%s\n", MISSING_NAME);
        my_free_arrays(1, sub);
        return (false);
    }
    command->info_out = strdup(sub[0]);
    replace_args(command, array[index], array[index + 1], env);
    my_free_arrays(1, sub);
    return (true);
}
