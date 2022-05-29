/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Functions to handle history
*/

#include <stdio.h>
#include <stdlib.h>
#include "shell.h"
#include "history.h"
#include "messages.h"
#include "my_arrays.h"
#include "my_math.h"

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

static void display_nb_history(list_t *history, char *const *args)
{
    size_t nb = atoi(args[1]) == 0 ? 1 : atoi(args[1]);
    history_t *elem = get_history(history, -nb);

    for (; nb > 0 && elem != NULL; nb--) {
        elem = get_history(history, -nb);
        printf("    %ld  %s  %s\n", elem->index, elem->time, elem->command);
    }
}

void builtin_history(shell_t *shell, char *const *args)
{
    list_t *history = shell->history;
    history_t *elem = NULL;
    size_t size = my_arraylen(args);

    if (is_history_error(args, true))
        return;
    if (size == 2) {
        display_nb_history(history, args);
        return;
    }
    while (history != NULL) {
        elem = history->data;
        printf("    %ld  %s  %s\n", elem->index, elem->time, elem->command);
        history = history->next;
    }
}

int silent_history(shell_t *shell, char *const *args)
{
    (void) shell;
    if (is_history_error(args, false))
        return (1);
    return (0);
}
