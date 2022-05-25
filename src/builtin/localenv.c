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
    if (size == 4 && strcmp(args[2], "=") == 0) {
        if (!isalpha(args[1][0]))
            fprintf(stderr, "set: Variable name must begin with a letter.\n");
        if (isalpha(args[1][0]) && !my_isalphanum_str(args[1]))
            fprintf(stderr, "set: Variable name must %s\n", NONALPHA);
        return;
    }
    for (size_t i = 1; i < size; i++) {
        if (!my_isalphanum_str(args[i])) {
            fprintf(stderr, "set: Variable name must %s\n", NONALPHA);
            return;
        }
    }
}

void builtin_unset(shell_t *shell, char *const *args)
{
    (void) shell;
    (void) args;
    return;
}

int silent_set(shell_t *shell, char *const *args)
{
    size_t size = my_arraylen(args);

    if (size == 4 && strcmp(args[2], "=") == 0) {
        if (!isalpha(args[1][0]) || !my_isalphanum_str(args[1]))
            return (1);
        add_localvar(&shell->localenv, args[1], args[3], false);
        return (0);
    }
    for (size_t i = 1; i < size; i++)
        if (!my_isalphanum_str(args[i]))
            return (1);
    for (size_t i = 1; i < size; i++)
        add_localvar(&shell->localenv, args[i], "", false);
    return (0);
}

int silent_unset(shell_t *shell, char *const *args)
{
    (void) shell;
    (void) args;
    return (0);
}
