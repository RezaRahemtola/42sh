/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** String checks
*/

#include <stdbool.h>
#include <stddef.h>
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

bool is_command_empty(command_t *command)
{
    const char *first = command->args[0];

    return (strlen(command->input) == 0 || first == NULL || strlen(first) == 0);
}
