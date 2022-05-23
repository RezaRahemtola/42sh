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

static void add_history(const char *input, shell_t *shell)
{
    history_t *elem = malloc(sizeof(history_t));
    size_t index = my_list_size(shell->history);
    time_t current_time = time(NULL);
    struct tm *now= localtime(&current_time);

    elem->index = index;
    elem->command = strdup(input);
    elem->time = malloc(sizeof(char) * 6);
    sprintf(elem->time, "%d:%d", now->tm_hour, now->tm_min);
    elem->command[strlen(elem->command) - 1] = '\0';
    my_list_add(&shell->history, elem);
}

static char *get_history_command(list_t *history, int index)
{
    history_t *elem = NULL;
    int size = my_list_size(history);

    if (index >= size || abs(index) > size)
        return (NULL);
    if (index < 0)
        index = size + index;
    for (int i = 0; i < index - 1; i++)
        history = history->next;
    elem = history->data;
    return (elem->command);
}

static void replace_last_command(char **input, list_t *history)
{
    char *new = NULL;

    if (my_list_size(history) == 0) {
        dprintf(2, "!!: Event not found.\n");
        free(*input);
        *input = NULL;
    } else {
        new = my_strrep(*input, "!!", get_history_command(history, -1));
        free(*input);
        *input = new;
        printf("%s", *input);
    }
}

void replace_history(char **input, shell_t *shell)
{
    if (strstr(*input, "!!") != NULL)
        replace_last_command(input, shell->history);
    if (*input != NULL)
        add_history(*input, shell);
    else
        *input = strdup(" ");
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
