/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Functions to interact with history elements
*/

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"
#include "my_string.h"

void add_history(const char *input, shell_t *shell)
{
    history_t *elem = malloc(sizeof(history_t));

    elem->index = my_list_size(shell->history);
    elem->command = strdup(input);
    elem->time = my_timestr();
    elem->command[strlen(elem->command) - 1] = '\0';
    my_list_add(&shell->history, elem);
}

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
    int size = my_list_size(history);

    if (index < 0)
        index = size + index;
    while (history != NULL) {
        elem = history->data;
        if (elem->index == (size_t)index)
            return (elem->command);
        history = history->next;
    }
    return (NULL);
}

char *get_history_by_str(list_t *history, const char *str)
{
    int len = my_list_size(history);
    int index = -1;
    char *cmd = NULL;

    while (len >= abs(index)) {
        cmd = get_history_command(history, index);
        if (strncmp(cmd, str, strlen(str)) == 0)
            return (cmd);
    }
    return (NULL);
}
