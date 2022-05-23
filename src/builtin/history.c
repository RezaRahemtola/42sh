/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Functions to handle history
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "shell.h"
#include "my_string.h"

void add_history_command(const char *input, shell_t *shell)
{
    history_t *elem = malloc(sizeof(history_t));
    size_t index = my_list_size(shell->history);
    time_t now = time(NULL);
    struct tm *current_time = localtime(&now);
    int hour = current_time->tm_hour;
    int min = current_time->tm_min;

    elem->index = index;
    elem->command = strdup(input);
    elem->time = malloc(sizeof(char) * 6);
    sprintf(elem->time, "%d:%d", hour, min);
    my_list_add(&shell->history, elem);
}

void free_history(void *elem)
{
    history_t *history = elem;

    free(history->command);
    free(history->time);
    free(history);
}

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
        printf("%ld\t%s\t%s", elem->index, elem->time, elem->command);
        history = history->next;
    }
    return (0);
}
