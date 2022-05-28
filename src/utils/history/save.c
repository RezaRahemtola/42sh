/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Functions to load and save history
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "environment.h"
#include "history.h"
#include "my_arrays.h"
#include "my_string.h"
#include "my.h"

static char *get_history_file_path(env_t *env)
{
    char *path = NULL;
    const env_t *home = get_env_value(env, "HOME");

    if (home == NULL)
        return (NULL);
    path = malloc(sizeof(char) * (strlen(home->value) + strlen(HISTORY_FILE)
    + 2));
    sprintf(path, "%s/%s", home->value, HISTORY_FILE);
    return (path);
}

static void add_loaded_elem(char **metadata, char *cmd, shell_t *shell)
{
    history_t *elem = malloc(sizeof(history_t));
    char *index = metadata[0];
    char *time = metadata[1];

    elem->index = atoi(index);
    time[strlen(time) - 1] = '\0';
    elem->time = strdup(time);
    cmd[strlen(cmd) - 1] = '\0';
    elem->command = strdup(cmd);
    my_list_add(&shell->history, elem);
    my_free_arrays(1, metadata);
}

void load_history(shell_t *shell)
{
    char *path = get_history_file_path(shell->env);
    FILE *file = NULL;
    char *line = NULL;
    char **args = NULL;
    size_t len = 0;

    if (path != NULL)
        file = fopen(path, "r");
    if (path == NULL || file == NULL) {
        free(path);
        return;
    }
    while (getline(&line, &len, file) != -1) {
        args = my_strsplit(line, ' ');
        if (my_arraylen(args) != 2 || getline(&line, &len, file) == -1)
            break;
        add_loaded_elem(args, line, shell);
    }
    fclose(file);
    my_free(2, line, path);
}

void save_history(list_t *history, env_t *env)
{
    char *path = get_history_file_path(env);
    FILE *file = NULL;
    history_t *elem = NULL;

    if (path != NULL)
        file = fopen(path, "w");
    if (path == NULL || file == NULL) {
        free(path);
        return;
    }
    while (history != NULL) {
        elem = history->data;
        fprintf(file, "%ld %s\n%s\n", elem->index, elem->time, elem->command);
        history = history->next;
    }
    fclose(file);
    free(path);
}
