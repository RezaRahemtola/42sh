/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Functions to handle history
*/

#include <stdio.h>
#include "shell.h"
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
    return (false);
}

void builtin_history(shell_t *shell, char *const *args)
{
    list_t *history = shell->history;
    history_t *elem = NULL;

    (void) shell;
    if (is_history_error(args, true))
        return;
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
