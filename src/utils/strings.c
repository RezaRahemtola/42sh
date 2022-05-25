/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** String checks
*/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"
#include "my_string.h"

char *get_next_argument(const char *str, size_t index)
{
    bool text = false;
    size_t size = strlen(str);
    size_t i = index;

    for (; i < size; i++) {
        if (str[i] != ' ' && str[i] != '\t')
            text = true;
        if ((str[i] == ' ' || str[i] == '\t') && text)
            break;
    }
    return (my_substr_size(str, index, index + i, size));
}

bool is_command_empty(const command_t *command)
{
    const char *first = command->args[0];

    return (strlen(command->input) == 0 || first == NULL || strlen(first) == 0);
}

char *join_array(char *const *array, size_t start, size_t end)
{
    char *str = NULL;
    size_t size = 0;
    size_t i = 0;

    for (size_t j = 0; j < end; j++)
        size += strlen(array[j + start]) + 1;
    str = malloc(sizeof(char) * size);
    if (str == NULL)
        return (NULL);
    for (size_t j = 0; j < end; j++) {
        if (j > 0) {
            str[i] = ' ';
            i++;
        }
        for (size_t k = 0; array[j + start][k] != '\0'; k++) {
            str[i] = array[j + start][k];
            i++;
        }
    }
    str[i] = '\0';
    return (str);
}
