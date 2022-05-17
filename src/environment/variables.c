/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Variables management
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "environment.h"

static bool is_alphanumeric(const char *str)
{
    size_t size = strlen(str);
    int number = 0;
    int lower = 0;
    int upper = 0;

    for (size_t i = 0; i < size; i++) {
        number = (str[i] >= '0' && str[i] <= '9');
        lower = (str[i] >= 'a' && str[i] <= 'z');
        upper = (str[i] >= 'A' && str[i] <= 'Z');
        if (!number && !lower && !upper && str[i] != '_')
            return (false);
    }
    return (true);
}

void add_variable(env_t **env, const char *key, const char *value)
{
    const env_t *var = get_env_value(*env, key);

    if (var == NULL)
        put_env_property(env, key, value);
    else
        replace_env_value(*env, key, value);
}

int set_variable(env_t **env, const char *key, const char *value)
{
    char *alpha = "alphanumeric characters";

    if (is_alphanumeric(key)) {
        add_variable(env, key, value);
        return (0);
    } else {
        fprintf(stderr, "setenv: Variable name must contain %s.\n", alpha);
        return (1);
    }
}

env_t *get_env_from_array(const char *const *env)
{
    env_t *list = NULL;
    char *key = NULL;
    char *value = NULL;

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

char *const *get_array_from_env(const env_t *list)
{
    size_t size = get_env_size(list);
    int index = 0;
    char **array = malloc(sizeof(char *) * (size + 1));
    const env_t *current = list;

    if (array == NULL)
        return NULL;
    while (current != NULL) {
        array[index] = malloc(sizeof(char) * (strlen(current->key) +
        strlen(current->value) + 2));
        sprintf(array[index], "%s=%s", current->key, current->value);
        index++;
        current = current->next;
    }
    array[index] = NULL;
    return (array);
}
