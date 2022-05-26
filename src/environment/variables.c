/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Variables management
*/

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "environment.h"
#include "messages.h"
#include "my_string.h"

void add_variable(env_t **env, const char *key, const char *value)
{
    const env_t *var = get_env_value(*env, key);

    if (var == NULL)
        put_env_property(env, key, value);
    else
        replace_env_value(*env, key, value);
}

env_t *get_env_from_array(const char *const *env)
{
    env_t *list = NULL;
    char *key = NULL;
    char *value = NULL;

    if (env == NULL)
        return (NULL);
    for (size_t i = 0; env[i] != NULL; i++) {
        key = extract_env_key(env[i]);
        value = extract_env_value(env[i]);
        if (key != NULL && value != NULL)
            put_env_property(&list, key, value);
        free(key);
        free(value);
    }
    return (list);
}

char *const *get_array_from_env(const env_t *env)
{
    size_t size = get_env_size(env);
    int index = 0;
    char **array = malloc(sizeof(char *) * (size + 1));

    if (array == NULL)
        return NULL;
    for (; env != NULL; index++) {
        array[index] = malloc(sizeof(char) * (strlen(env->key) +
        strlen(env->value) + 2));
        sprintf(array[index], "%s=%s", env->key, env->value);
        env = env->next;
    }
    array[index] = NULL;
    return (array);
}
