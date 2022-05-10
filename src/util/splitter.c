/*
** EPITECH PROJECT, 2022
** minishell2
** File description:
** Custom redirections splitter
*/

#include <stdlib.h>
#include <string.h>
#include "minishell.h"
#include "my_string.h"
#include "redirections.h"

redirection_t get_redirection(char *str, size_t index)
{
    redirection_t empty = { NULL, NULL };

    for (size_t i = 0; REDIRECTIONS[i].type != NULL; i++) {
        if (my_str_starts(&str[index], REDIRECTIONS[i].type) == 0) {
            return (REDIRECTIONS[i]);
        }
    }
    return (empty);
}

static size_t count_redirections(char *str, size_t size)
{
    size_t count = 1;
    redirection_t redirect = { 0, 0 };

    for (size_t i = 0; i < size; i++) {
        redirect = get_redirection(str, i);
        if (redirect.type != NULL) {
            count += 2;
            i += strlen(redirect.type) - 1;
        }
    }
    return (count);
}

static void append_end(char **array, char *input, size_t pattern, int index)
{
    size_t size = strlen(input);
    char *end = my_substr_size(input, (int) pattern, (int) size, (int) size);

    array[index] = end;
    array[index + 1] = NULL;
}

char **split_redirections(char *input)
{
    int index = 0;
    size_t pattern = 0;
    size_t size = strlen(input);
    size_t count = count_redirections(input, size);
    redirection_t redirect = { 0, 0 };
    char **array = malloc(sizeof(char *) * (count + 1));

    for (size_t i = 0; i < size; i++) {
        redirect = get_redirection(input, i);
        if (redirect.type != NULL) {
            array[index] = my_substr_size(input, (int) pattern, (int) i,
                (int) size);
            array[index + 1] = strdup(redirect.type);
            pattern = i + strlen(redirect.type);
            index += 2;
            i += strlen(redirect.type) - 1;
        }
    }
    append_end(array, input, pattern, index);
    return (array);
}
