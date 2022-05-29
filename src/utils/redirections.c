/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Custom redirections splitter
*/

#include <stdlib.h>
#include <string.h>
#include "my_string.h"
#include "redirections.h"
#include "shell.h"

redirection_t get_redirection(const char *str, size_t index)
{
    size_t len = 0;

    for (size_t i = 0; REDIRECTIONS[i].type != NULL; i++) {
        len = strlen(REDIRECTIONS[i].type);
        if (strncmp(&str[index], REDIRECTIONS[i].type, len) == 0)
            return (REDIRECTIONS[i]);
    }
    return (redirection_t) {NULL, NULL};
}

static size_t count_redirections(const char *str, size_t size)
{
    size_t count = 1;
    redirection_t redirect = {NULL, NULL};

    for (size_t i = 0; i < size; i++) {
        redirect = get_redirection(str, i);
        if (redirect.type != NULL) {
            count += 2;
            i += strlen(redirect.type) - 1;
        }
    }
    return (count);
}

char **split_redirections(const char *input)
{
    size_t index = 0;
    size_t pattern = 0;
    size_t size = strlen(input);
    size_t count = count_redirections(input, size);
    redirection_t redirect = {NULL, NULL};
    char **array = malloc(sizeof(char *) * (count + 1));

    for (size_t i = 0; i < size; i++) {
        redirect = get_redirection(input, i);
        if (redirect.type != NULL) {
            array[index] = my_substr_size(input, pattern, i, size);
            array[index + 1] = strdup(redirect.type);
            pattern = i + strlen(redirect.type);
            index += 2;
            i += strlen(redirect.type) - 1;
        }
    }
    append_end(array, input, pattern, index);
    return (array);
}
