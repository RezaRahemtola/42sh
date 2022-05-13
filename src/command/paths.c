/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Path handling
*/

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "my_arrays.h"
#include "my_string.h"
#include "environment.h"

static char *explore_path(env_t *path, const char *bin)
{
    char **array = my_strsplit(path->value, ':');
    size_t size = my_arraylen(array);
    char *line = NULL;
    char *separator = NULL;

    for (size_t i = 0; i < size; i++) {
        separator = (array[i][strlen(array[i]) - 1] == '/' ? "" : "/");
        line = malloc(sizeof(char) * (strlen(array[i]) + strlen(bin)
                                      + strlen(separator) + 1));
        sprintf(line, "%s%s%s", array[i], separator, bin);
        if (access(line, F_OK) == 0) {
            my_free_arrays(1, array);
            return (line);
        }
        free(line);
        line = NULL;
    }
    my_free_arrays(1, array);
    return (NULL);
}

char *find_command(env_t *env, const char *bin)
{
    env_t *path = get_env_value(env, "PATH");

    if (bin == NULL)
        return (NULL);
    if (my_str_contains(bin, "/") == 0)
        return (access(bin, F_OK) == -1 ? NULL : strdup(bin));
    else if (path == NULL)
        return NULL;
    else
        return (explore_path(path, bin));
}
