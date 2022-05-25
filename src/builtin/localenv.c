/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Functions for local env builtins
*/

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "environment.h"
#include "messages.h"
#include "my_string.h"
#include "my_arrays.h"

void builtin_set(shell_t *shell, char *const *args)
{
    size_t size = my_arraylen(args);

    if (size == 1) {
        print_localenv(shell->localenv);
        return;
    }
    if (size == 4 && strcmp(args[2], "=") == 0 && !isalpha(args[1][0])) {
        fprintf(stderr, "set: Variable name must begin with a letter.\n");
        return;
    }
    if (size == 4 && strcmp(args[2], "=") == 0 && !my_isalphanum_str(args[1])) {
        fprintf(stderr, "set: Variable name must %s\n", NONALPHA);
        return;
    }
}

void builtin_unset(shell_t *shell, char *const *args)
{
    return;
}

int silent_set(shell_t *shell, char *const *args)
{
    size_t size = my_arraylen(args);

    if (size == 4 && strcmp(args[2], "=") == 0) {
        if (!isalpha(args[1][0]) || !my_isalphanum_str(args[1]))
            return (1);
        else
            add_localvar(&shell->localenv, args[1], args[3], false);
    }
    return (0);
}

int silent_unset(shell_t *shell, char *const *args)
{
    return (0);
}
