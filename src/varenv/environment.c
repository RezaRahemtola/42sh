/*
** EPITECH PROJECT, 2021
** minishell2
** File description:
** Environment variables
*/

#include <stdlib.h>
#include "minishell.h"
#include "my_string.h"
#include "my.h"

char *extract_key(char const *var)
{
    int size = my_strlen(var);

    for (int i = 0; i < size; i++) {
        if (var[i] == '=') {
            return (my_substr_size(var, 0, i, size));
        }
    }
    return (NULL);
}

char *extract_value(char const *var)
{
    int size = my_strlen(var);

    for (int i = 0; i < size; i++) {
        if (var[i] == '=') {
            return (my_substr_size(var, i + 1, size, size));
        }
    }
    return (NULL);
}

void print_env(varenv_t *env)
{
    varenv_t *current = env;

    while (current != NULL) {
        my_printf("%s=%s\n", current->key, current->value);
        current = current->next;
    }
}

void destroy_env(varenv_t *env)
{
    varenv_t *current = env;
    varenv_t *tmp = NULL;

    while (current != NULL) {
        tmp = current->next;
        free(current->key);
        free(current->value);
        free(current);
        current = tmp;
    }
}
