/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Functions to interact with history elements
*/

#include <stdlib.h>
#include <string.h>
#include "types.h"

void free_history(void *elem)
{
    history_t *history = elem;

    free(history->command);
    free(history->time);
    free(history);
}

history_t *get_history(list_t *history, int index)
{
    history_t *elem = NULL;

    if (history == NULL)
        return (NULL);
    while (true) {
        elem = history->data;
        if (elem->index == (size_t)index)
            return (elem);
        if (history->next == NULL)
            break;
        history = history->next;
    }
    while (index < 0 && history != NULL) {
        elem = history->data;
        index += 1;
        if (index == 0)
            return (elem);
        history = history->prev;
    }
    return (NULL);
}

char *get_history_by_str(list_t *history, const char *str, bool contains)
{
    int len = my_list_size(history);
    history_t *hist = NULL;

    for (int index = -1; len >= abs(index); index--) {
        hist = get_history(history, index);
        if (!contains && strncmp(hist->command, str, strlen(str)) == 0)
            return (hist->command);
        if (contains && strstr(hist->command, str) != NULL)
            return (hist->command);
    }
    return (NULL);
}
