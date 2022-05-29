/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Functions to handle history
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "shell.h"
#include "history.h"
#include "environment.h"
#include "messages.h"
#include "my_arrays.h"
#include "my_math.h"
#include "my.h"

static bool is_history_error(char *const *args, bool print)
{
    size_t size = my_arraylen(args);

    if (size >= 2 && !my_is_number(args[1])) {
        if (print)
            fprintf(stderr, "history: %s\n", NUMBER_ERROR);
        return (true);
    }
    if (size >= 2 && atoi(args[1]) < 0) {
        if (print)
            fprintf(stderr, "%s\n", HISTORY_USAGE);
        return (true);
    }
    return (false);
}

static int compute_max_history(shell_t *shell, const char *arg)
{
    const localenv_t *env = get_localenv_value(shell->localenv, "history");
    int len = my_list_size(shell->history);
    int nb = (arg != NULL ? (atoi(arg) == 0 ? 1 : atoi(arg)) : 0);
    int env_max = 0;

    if (env == NULL && arg == NULL)
        return (MIN(len, INT_MAX));
    if (env == NULL && arg != NULL)
        return (MIN(len, nb));
    env_max = atoi(env->value) == 0 ? 1 : atoi(env->value);
    if (arg == NULL && env != NULL)
        return (MIN(len, env_max));
    return (MIN(len, MIN(env_max, nb)));
}

static void display_nb_history(list_t *history, int nb)
{
    history_t *elem = get_history(history, -nb);

    for (; nb > 0 && elem != NULL; nb--) {
        elem = get_history(history, -nb);
        printf("    %ld  %s  %s\n", elem->index, elem->time, elem->command);
    }
}

void builtin_history(shell_t *shell, char *const *args)
{
    list_t *history = shell->history;
    size_t size = my_arraylen(args);
    int nb = 0;
    const char *arg = (size == 2 ? args[1] : NULL);

    if (is_history_error(args, true))
        return;
    nb = compute_max_history(shell, arg);
    display_nb_history(history, nb);
}

int silent_history(shell_t *shell, char *const *args)
{
    (void) shell;
    if (is_history_error(args, false))
        return (1);
    return (0);
}
