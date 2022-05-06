/*
** EPITECH PROJECT, 2022
** minishell2
** File description:
** String checks
*/

#include <stdbool.h>
#include <stddef.h>
#include "minishell.h"
#include "my_string.h"

char *get_next_argument(char *str, int index)
{
    bool text = false;
    bool out = false;
    int size = my_strlen(str);
    int i = index;

    for (i = index; i < size && !out; i++) {
        if (str[i] != ' ' && str[i] != '\t') {
            text = true;
        }
        out = ((str[i] == ' ' || str[i] == '\t') && text);
    }
    return (my_substr_size(str, index, index + i, size));
}

bool is_command_empty(command_t *command)
{
    int input = my_strlen(command->input);
    char *first = command->args[0];

    return (input == 0 || first == NULL || my_strlen(first) == 0);
}
