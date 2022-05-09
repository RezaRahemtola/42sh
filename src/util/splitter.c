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

redirection_t get_redirection(char *str, int index)
{
    redirection_t empty = { NULL, NULL };

    for (int i = 0; REDIRECTIONS[i].type != NULL; i++) {
        if (my_str_starts(&str[index], REDIRECTIONS[i].type) == 0) {
            return (REDIRECTIONS[i]);
        }
    }
    return (empty);
}

static int count_redirections(char *str, int size)
{
    int count = 1;
    redirection_t redirect = { 0, 0 };

    for (int i = 0; i < size; i++) {
        redirect = get_redirection(str, i);
        if (redirect.type != NULL) {
            count += 2;
            i += strlen(redirect.type) - 1;
        }
    }
    return (count);
}

static void append_end(char **array, char *input, int pattern, int index)
{
    int size = strlen(input);
    char *end = my_substr_size(input, pattern, size, size);

    array[index] = end;
    array[index + 1] = NULL;
}

char **split_redirections(char *input)
{
    int index = 0;
    int pattern = 0;
    int size = strlen(input);
    int count = count_redirections(input, size);
    redirection_t redirect = { 0, 0 };
    char **array = malloc(sizeof(char *) * (count + 1));

    for (int i = 0; i < size; i++) {
        redirect = get_redirection(input, i);
        if (redirect.type != NULL) {
            array[index] = my_substr_size(input, pattern, i, size);
            array[index + 1] = my_strdup(redirect.type);
            pattern = i + strlen(redirect.type);
            index += 2;
            i += strlen(redirect.type) - 1;
        }
    }
    append_end(array, input, pattern, index);
    return (array);
}
