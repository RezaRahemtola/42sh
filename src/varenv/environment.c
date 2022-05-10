/*
** EPITECH PROJECT, 2021
** minishell2
** File description:
** Environment variables
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "minishell.h"
#include "my_string.h"

char *extract_key(char const *var)
{
    size_t size = strlen(var);

    for (size_t i = 0; i < size; i++) {
        if (var[i] == '=') {
            return (my_substr_size(var, 0, (int) i, (int) size));
        }
    }
    return (NULL);
}

char *extract_value(char const *var)
{
    size_t size = strlen(var);

    for (size_t i = 0; i < size; i++) {
        if (var[i] == '=') {
            return (my_substr_size(var, (int) i + 1, (int) size, (int) size));
        }
    }
    return (NULL);
}

void print_env(varenv_t *env)
{
    varenv_t *current = env;

    while (current != NULL) {
        printf("%s=%s\n", current->key, current->value);
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
