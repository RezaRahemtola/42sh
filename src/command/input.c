/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Input redirection checks
*/

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "messages.h"
#include "my_string.h"
#include "my_arrays.h"
#include "redirections.h"

bool is_valid_redirection(const command_t *command, char *const *array,
    bool is_input)
{
    if (array[1] == NULL || strlen(array[1]) == 0) {
        fprintf(stderr, "%s\n", MISSING_NAME);
        return (false);
    }
    if ((is_input ? command->separator_in : command->separator_out) != 0) {
        fprintf(stderr, "%s\n", is_input ? AMBIGUOUS_INPUT : AMBIGUOUS_OUTPUT);
        return (false);
    }
    return (true);
}

bool check_in_file(command_t *cmd, char *const *array, const env_t *env)
{
    char *const *sub = NULL;

    if (!is_valid_redirection(cmd, array, true))
        return (false);
    cmd->separator_in = FILE_READ;
    sub = my_strsplit_many(array[1], " \t");
    if (sub == NULL)
        return (false);
    if (sub[0] == NULL || strlen(sub[0]) == 0) {
        fprintf(stderr, "%s\n", MISSING_NAME);
        my_free_arrays(1, sub);
        return (false);
    }
    cmd->info_in = strdup(sub[0]);
    replace_args(cmd, array[0], array[1], env);
    my_free_arrays(1, sub);
    return (true);
}

bool check_in_input(command_t *cmd, char *const *array, const env_t *env)
{
    char *const *sub = NULL;

    if (!is_valid_redirection(cmd, array, true))
        return (false);
    cmd->separator_in = INPUT_READ;
    sub = my_strsplit_many(array[1], " \t");
    if (sub == NULL)
        return (false);
    if (sub[0] == NULL || strlen(sub[0]) == 0) {
        fprintf(stderr, "%s\n", MISSING_NAME);
        my_free_arrays(1, sub);
        return (false);
    }
    cmd->info_in = strdup(sub[0]);
    replace_args(cmd, array[0], array[1], env);
    my_free_arrays(1, sub);
    return (true);
}
