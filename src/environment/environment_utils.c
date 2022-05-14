/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Environment variables
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "shell.h"
#include "my_string.h"

char *extract_env_key(const char *var)
{
    size_t size = strlen(var);

    for (size_t i = 0; i < size; i++)
        if (var[i] == '=')
            return (my_substr_size(var, 0, i, size));
    return (NULL);
}

char *extract_env_value(const char *var)
{
    size_t size = strlen(var);

    for (size_t i = 0; i < size; i++)
        if (var[i] == '=')
            return (my_substr_size(var, i + 1, size, size));
    return (NULL);
}

void print_env(const env_t *env)
{
    const env_t *current = env;

    while (current != NULL) {
        printf("%s=%s\n", current->key, current->value);
        current = current->next;
    }
}

void destroy_env(env_t *env)
{
    env_t *current = env;
    env_t *tmp = NULL;

    while (current != NULL) {
        tmp = current->next;
        free(current->key);
        free(current->value);
        free(current);
        current = tmp;
    }
}
