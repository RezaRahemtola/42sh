/*
** EPITECH PROJECT, 2022
** minishell2
** File description:
** Input redirection checks
*/

#include <stddef.h>
#include "messages.h"
#include "my_string.h"
#include "my.h"
#include "redirections.h"

static bool check_null_ambiguous(command_t *command, char **array, int index)
{
    if (array[index + 1] == NULL || my_strlen(array[index + 1]) == 0) {
        my_dprintf(2, "%s\n", MISSING_NAME);
        return (false);
    } else if (command->separator_in != NO_IN) {
        my_dprintf(2, "%s\n", AMBIGUOUS_INPUT);
        return (false);
    }
    return (true);
}

bool check_in_file(command_t *command, char **array, int index, \
varenv_t *env)
{
    char **sub = NULL;

    if (!check_null_ambiguous(command, array, index)) {
        return (false);
    }
    command->separator_in = FILE_READ;
    sub = my_strsplit_many(array[index + 1], " \t");
    if (sub == NULL) {
        return (false);
    } else if (sub[0] == NULL || my_strlen(sub[0]) == 0) {
        my_dprintf(2, "%s\n", MISSING_NAME);
        my_free_arrays(1, sub);
        return (false);
    }
    command->info_in = my_strdup(sub[0]);
    replace_args(command, array[index], array[index + 1], env);
    my_free_arrays(1, sub);
    return (true);
}

bool check_in_input(command_t *command, char **array, int index, \
varenv_t *env)
{
    char **sub = NULL;

    if (!check_null_ambiguous(command, array, index)) {
        return (false);
    }
    command->separator_in = INPUT_READ;
    sub = my_strsplit_many(array[index + 1], " \t");
    if (sub == NULL) {
        return (false);
    } else if (sub[0] == NULL || my_strlen(sub[0]) == 0) {
        my_dprintf(2, "%s\n", MISSING_NAME);
        my_free_arrays(1, sub);
        return (false);
    }
    command->info_in = my_strdup(sub[0]);
    replace_args(command, array[index], array[index + 1], env);
    my_free_arrays(1, sub);
    return (true);
}
