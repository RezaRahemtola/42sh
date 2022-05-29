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

char *get_history_command(list_t *history, int index)
{
    history_t *elem = NULL;
    bool backward = (index < 0);

    if (history == NULL)
        return (NULL);
    while (true) {
        elem = history->data;
        if (elem->index == (size_t)index)
            return (elem->command);
        if (history->next == NULL)
            break;
        history = history->next;
    }
    while (backward && history != NULL) {
        elem = history->data;
        index += 1;
        if (index == 0)
            return (elem->command);
        history = history->prev;
    }
    return (NULL);
}

char *get_history_by_str(list_t *history, const char *str)
{
    int len = my_list_size(history);
    char *cmd = NULL;

    for (int index = -1; len >= abs(index); index--) {
        cmd = get_history_command(history, index);
        if (strncmp(cmd, str, strlen(str)) == 0)
            return (cmd);
    }
    return (NULL);
}
