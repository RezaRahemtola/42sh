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
#include "my_string.h"
#include "my_arrays.h"

void builtin_set(shell_t *shell, char *const *args)
{
    size_t size = my_arraylen(args);
    bool readonly = (size >= 2 && strcmp(args[1], "-r") == 0);
    size_t i = readonly ? 2 : 1;

    if (size == 1 || (size == 2 && readonly)) {
        print_localenv(shell->localenv, readonly);
        return;
    }
    if (size == i + 3 && strcmp(args[i + 1], "=") == 0) {
        is_valid_localvar(args[i], shell->localenv, true);
        return;
    }
    for (; i < size && is_valid_localvar(args[i], shell->localenv, true); i++);
}

void builtin_unset(shell_t *shell, char *const *args)
{
    size_t size = my_arraylen(args);

    if (size == 1)
        fprintf(stderr, "unset: Too few arguments.\n");
    for (size_t i = 1; i < size; i++) {
        if (is_localvar_readonly(shell->localenv, args[i])) {
            fprintf(stderr, "unset: $%s is read-only.\n", args[i]);
            return;
        }
    }
}

int silent_set(shell_t *shell, char *const *args)
{
    size_t size = my_arraylen(args);
    bool readonly = (size >= 2 && strcmp(args[1], "-r") == 0);
    size_t i = readonly ? 2 : 1;

    if (size == i + 3 && strcmp(args[i + 1], "=") == 0) {
        if (!is_valid_localvar(args[i], shell->localenv, false))
            return (1);
        add_localvar(&shell->localenv, args[i], args[i + 2], readonly);
        return (0);
    }
    for (; i < size; i++) {
        if (is_valid_localvar(args[i], shell->localenv, false))
            add_localvar(&shell->localenv, args[i], "", readonly);
        else
            return (1);
    }
    return (0);
}

int silent_unset(shell_t *shell, char *const *args)
{
    size_t size = my_arraylen(args);

    if (size == 1)
        return (1);
    for (size_t i = 1; i < size; i++) {
        if (!is_localvar_readonly(shell->localenv, args[i]))
            remove_localenv_property(&shell->localenv, args[i]);
        else
            return (1);
    }
    return (0);
}
