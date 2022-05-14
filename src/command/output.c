/*
** EPITECH PROJECT, 2022
** 42sh
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

bool check_out_append(command_t *cmd, char *const *array, const env_t *env)
{
    char *const *sub = NULL;

    if (!is_valid_redirection(cmd, array, false))
        return (false);
    cmd->separator_out = FILE_APPEND;
    sub = my_strsplit_many(array[1], " \t");
    if (sub == NULL)
        return (false);
    if (sub[0] == NULL || strlen(sub[0]) == 0) {
        fprintf(stderr, "%s\n", MISSING_NAME);
        my_free_arrays(1, sub);
        return (false);
    }
    cmd->info_out = strdup(sub[0]);
    replace_args(cmd, array[0], array[1], env);
    my_free_arrays(1, sub);
    return (true);
}

bool check_out_write(command_t *cmd, char *const *array, const env_t *env)
{
    char *const *sub = NULL;

    if (!is_valid_redirection(cmd, array, false))
        return (false);
    cmd->separator_out = FILE_WRITE;
    sub = my_strsplit_many(array[1], " \t");
    if (sub == NULL)
        return (false);
    if (sub[0] == NULL || strlen(sub[0]) == 0) {
        fprintf(stderr, "%s\n", MISSING_NAME);
        my_free_arrays(1, sub);
        return (false);
    }
    cmd->info_out = strdup(sub[0]);
    replace_args(cmd, array[0], array[1], env);
    my_free_arrays(1, sub);
    return (true);
}
