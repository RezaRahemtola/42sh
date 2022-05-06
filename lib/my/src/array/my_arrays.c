/*
** EPITECH PROJECT, 2022
** libmy
** File description:
** Arrays manipulation functions
*/

#include <stdlib.h>
#include "my_arrays.h"
#include "my_string.h"

static void free_in(char **array, int size)
{
    for (int i = 0; i < size; i++) {
        free(array[i]);
    }
    free(array);
}

char **my_arraydup(char **array)
{
    int size = my_arraylen(array);
    char **new = malloc(sizeof(char *) * (size + 1));

    if (new == NULL) {
        return (NULL);
    }
    for (int i = 0; i < size; i++) {
        new[i] = my_strdup(array[i]);
        if (new[i] == NULL) {
            free_in(new, i);
            return (NULL);
        }
    }
    new[size] = NULL;
    return (new);
}

int my_arraylen(char * const *array)
{
    int size = 0;

    for (size = 0; array[size] != NULL; size++);
    return (size);
}
