/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Custom logical operators splitter
*/

#include <stdlib.h>
#include <string.h>
#include "logical.h"
#include "my_string.h"

logical_t get_logical(const char *str, size_t index)
{
    for (size_t i = 0; LOGICAL[i].type != NULL; i++)
        if (my_str_starts(&str[index], LOGICAL[i].type) == 0)
            return (LOGICAL[i]);
    return (logical_t) {NULL, NULL};
}

static size_t count_logical(const char *str, size_t size)
{
    size_t count = 1;
    logical_t logical = {NULL, NULL};

    for (size_t i = 0; i < size; i++) {
        logical = get_logical(str, i);
        if (logical.type != NULL) {
            count += 2;
            i += strlen(logical.type) - 1;
        }
    }
    return (count);
}

static void append_end(char **array, const char *input, size_t pattern, \
int index)
{
    size_t size = strlen(input);
    char *end = my_substr_size(input, pattern, size, size);

    array[index] = end;
    array[index + 1] = NULL;
}

char **split_logical(const char *input)
{
    int index = 0;
    size_t pattern = 0;
    size_t size = strlen(input);
    size_t count = count_logical(input, size);
    logical_t logical = {NULL, NULL};
    char **array = malloc(sizeof(char *) * (count + 1));

    for (size_t i = 0; i < size; i++) {
        logical = get_logical(input, i);
        if (logical.type != NULL) {
            array[index] = my_substr_size(input, pattern, i, size);
            array[index + 1] = strdup(logical.type);
            pattern = i + strlen(logical.type);
            index += 2;
            i += strlen(logical.type) - 1;
        }
    }
    append_end(array, input, pattern, index);
    return (array);
}
