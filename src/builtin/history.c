/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Functions to handle history
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "shell.h"
#include "my_string.h"
#include "my_math.h"

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

static void replace_last_command(char **input, list_t *history)
{
    char *new = NULL;

    if (my_list_size(history) == 0) {
        dprintf(2, "0: Event not found.\n");
        free(*input);
        *input = NULL;
    } else {
        new = my_strrep(*input, "!!", get_history_command(history, -1));
        free(*input);
        *input = new;
    }
}

static void handle_nb_substitution(char **input, char *current, list_t *history)
{
    int nb = atoi(current);
    char *cmd = get_history_command(history, nb);
    char *pattern = NULL;
    char *new = NULL;

    if (cmd == NULL) {
        dprintf(2, "%d: Event not found.\n", nb);
        free(*input);
        *input = NULL;
    } else {
        pattern = malloc(sizeof(char) * (my_nbrlen(nb) + 2));
        sprintf(pattern, "!%d", nb);
        new = my_strrep(*input, pattern, cmd);
        free(*input);
        *input = new;
        free(pattern);
    }
}

static void make_history_substitutions(char **input, list_t *history)
{
    char *new = strchr(*input, '!');

    while (new != NULL && *input != NULL) {
        if (isdigit(new[1]))
            handle_nb_substitution(input, &new[1], history);
        new = strchr(++new, '!');
    }
}

void replace_history(char **input, shell_t *shell)
{
    char *old = strdup(*input);

    if (strstr(*input, "!!") != NULL)
        replace_last_command(input, shell->history);
    if (strchr(*input, '!') != NULL)
        make_history_substitutions(input, shell->history);
    if (strcmp(*input, old) != 0)
        printf("%s", *input);
    if (*input != NULL)
        add_history(*input, shell);
    else
        *input = strdup(" ");
    free(old);
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
        printf("%ld\t%s\t%s\n", elem->index, elem->time, elem->command);
        history = history->next;
    }
    return (0);
}
