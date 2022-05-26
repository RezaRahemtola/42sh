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

static bool is_valid_multiset(char *const *args, bool readonly, bool print)
{
    size_t size = my_arraylen(args);
    size_t i = readonly ? 2 : 1;

    for (; i < size; i++) {
        if (!my_isalphanum_str(args[i])) {
            if (print)
                fprintf(stderr, "set: Variable name must %s\n", NONALPHA);
            return (false);
        }
    }
    return (true);
}

static bool is_valid_set(char *const *args, bool readonly, bool print)
{
    size_t var_idx = readonly ? 2 : 1;

    if (!isalpha(args[var_idx][0])) {
        if (print)
            fprintf(stderr, "set: Variable name must begin with a letter.\n");
        return (false);
    }
    if (!my_isalphanum_str(args[var_idx])) {
        if (print)
            fprintf(stderr, "set: Variable name must %s\n", NONALPHA);
        return (false);
    }
    return (true);
}

void builtin_set(shell_t *shell, char *const *args)
{
    size_t size = my_arraylen(args);
    bool readonly = (size >= 2 && strcmp(args[1], "-r") == 0);
    size_t i = readonly ? 2 : 1;

    if (size == 1 || (size == 2 && readonly)) {
        print_localenv(shell->localenv, readonly);
        return;
    }
    if (size == i + 3 && strcmp(args[i + 1], "=") == 0)
        is_valid_set(args, readonly, true);
    else
        is_valid_multiset(args, readonly, true);
}

void builtin_unset(shell_t *shell, char *const *args)
{
    size_t size = my_arraylen(args);

    (void) shell;
    if (size == 1)
        fprintf(stderr, "unset: Too few arguments.\n");
}

int silent_set(shell_t *shell, char *const *args)
{
    size_t size = my_arraylen(args);
    bool readonly = (size >= 2 && strcmp(args[1], "-r") == 0);
    size_t i = readonly ? 2 : 1;

    if (size == i + 3 && strcmp(args[i + 1], "=") == 0) {
        if (!is_valid_set(args, readonly, false))
            return (1);
        add_localvar(&shell->localenv, args[i], args[i + 2], readonly);
        return (0);
    }
    if (!is_valid_multiset(args, readonly, false))
        return (1);
    for (; i < size; i++)
        add_localvar(&shell->localenv, args[i], "", readonly);
    return (0);
}

int silent_unset(shell_t *shell, char *const *args)
{
    size_t size = my_arraylen(args);

    (void) shell;
    if (size == 1)
        return (1);
    for (size_t i = 1; i < size; i++)
        remove_localenv_property(&shell->localenv, args[i]);
    return (0);
}
