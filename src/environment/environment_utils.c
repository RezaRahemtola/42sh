/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Environment variables
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_string.h"
#include "shell.h"

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
    while (env != NULL) {
        printf("%s=%s\n", env->key, env->value);
        env = env->next;
    }
}

void destroy_env(env_t *env)
{
    env_t *tmp = NULL;

    while (env != NULL) {
        tmp = env->next;
        free(env->key);
        free(env->value);
        free(env);
        env = tmp;
    }
}
