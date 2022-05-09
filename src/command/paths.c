/*
** EPITECH PROJECT, 2022
** minishell2
** File description:
** Path handling
*/

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "my_arrays.h"
#include "my_string.h"
#include "my.h"
#include "varenv.h"

static char *explore_path(varenv_t *path, char *bin)
{
    char **array = my_strsplit(path->value, ':');
    int size = my_arraylen(array);
    char *line = NULL;

    for (int i = 0; i < size; i++) {
        line = (array[i][strlen(array[i]) - 1] == '/' ? "" : "/");
        line = my_stringf("%s%s%s", array[i], line, bin);
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

char *find_command(varenv_t *env, char *bin)
{
    varenv_t *path = varenv_get(env, "PATH");

    if (bin == NULL) {
        return (NULL);
    }
    if (my_str_contains(bin, "/") == 0) {
        return (access(bin, F_OK) == -1 ? NULL : my_strdup(bin));
    } else if (path == NULL) {
        return (NULL);
    } else {
        return (explore_path(path, bin));
    }
}
