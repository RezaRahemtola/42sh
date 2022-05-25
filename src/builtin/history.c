/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Functions to handle history
*/

#include <stdio.h>
#include "shell.h"

void builtin_history(env_t **env, char *const *args)
{
    (void)env;
    (void)args;
}

int silent_history(env_t **env, char *const *args, shell_t *shell)
{
    size_t size = my_list_size(shell->history);
    list_t *history = shell->history;
    history_t *elem = NULL;

    (void)env;
    (void)args;
    for (size_t i = 0; i < size; i++) {
        elem = history->data;
        printf("    %ld  %s  %s\n", elem->index, elem->time, elem->command);
        history = history->next;
    }
    return (0);
}
