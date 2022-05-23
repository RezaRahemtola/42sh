/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Functions to handle history
*/

#include <stdio.h>
#include "shell.h"
#include "my_string.h"

void builtin_history(env_t **env, char *const *args)
{
    (void)env;
    (void)args;
}

int silent_history(env_t **env, char *const *args, shell_t *shell)
{
    size_t size = my_list_size(shell->history);
    list_t *history = shell->history;

    (void)env;
    (void)args;
    for (size_t i = 0; i < size; i++) {
        printf("%ld\t%s", i, (char *)history->data);
        history = history->next;
    }
    return (0);
}
