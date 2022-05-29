/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Path handling
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "environment.h"
#include "my_arrays.h"
#include "my_string.h"

static char *explore_path(const env_t *path, const char *bin)
{
    char **array = my_strsplit(path->value, ':');
    size_t size = my_arraylen(array);
    char *line = NULL;
    char *separator = NULL;
    size_t len = 0;

    for (size_t i = 0; i < size; i++) {
        separator = (array[i][strlen(array[i]) - 1] == '/' ? "" : "/");
        len = snprintf(NULL, 0, "%s%s%s", array[i], separator, bin) + 1;
        line = malloc(sizeof(char) * len);
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

char *find_command(const env_t *env, const char *bin)
{
    const env_t *path = get_env_value(env, "PATH");

    if (bin == NULL)
        return (NULL);
    if (strchr(bin, '/') != NULL)
        return (access(bin, F_OK) == -1 ? NULL : strdup(bin));
    if (path == NULL)
        return NULL;
    return (explore_path(path, bin));
}
