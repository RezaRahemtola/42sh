/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Functions to add history elements
*/

#include <stdlib.h>
#include <string.h>
#include "history.h"
#include "my_string.h"

static size_t get_max_index(list_t *history)
{
    size_t max = 0;
    history_t *elem = NULL;

    while (history != NULL) {
        elem = history->data;
        max = elem->index;
        history = history->next;
    }
    return (max);
}

static bool delete_func(void *list_elem, void *compare)
{
    history_t *old = list_elem;
    history_t *new = compare;

    return (strcmp(old->command, new->command) == 0);
}

void add_history(const char *input, shell_t *shell)
{
    history_t *elem = malloc(sizeof(history_t));

    elem->index = get_max_index(shell->history) + 1;
    elem->command = strdup(input);
    elem->time = my_timestr();
    elem->command[strlen(elem->command) - 1] = '\0';
    my_list_remove(&shell->history, elem, delete_func, free_history);
    my_list_add(&shell->history, elem);
}
