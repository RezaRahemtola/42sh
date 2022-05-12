/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Map management
*/

#include <stdlib.h>
#include <string.h>
#include "shell.h"
#include "my.h"

env_t *get_env_value(env_t *list, const char *key)
{
    env_t *current = list;

    while (current != NULL) {
        if (strcmp(current->key, key) == 0)
            return (current);
        current = current->next;
    }
    return (NULL);
}

void put_env_property(env_t **list, const char *key, const char *value)
{
    env_t *env = malloc(sizeof(env_t));
    env_t *current = *list;

    if (env == NULL)
        return;
    env->key = strdup(key);
    env->value = strdup(value);
    env->next = NULL;
    if (*list == NULL)
        *list = env;
    else {
        while (current->next != NULL)
            current = current->next;
        current->next = env;
    }
}

void replace_env_value(env_t *list, const char *key, const char *value)
{
    env_t *current = list;

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            free(current->value);
            current->value = strdup(value);
            return;
        }
        current = current->next;
    }
}

void remove_env_property(env_t **list, const char *key)
{
    env_t *current = *list;
    env_t *prev = *list;

    if (strcmp(current->key, key) == 0) {
        *list = current->next;
        my_free(3, current->key, current->value, current);
        return;
    }
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            prev->next = current->next;
            my_free(3, current->key, current->value, current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

int get_env_size(env_t *list)
{
    int size = 0;
    env_t *current = list;

    while (current != NULL) {
        size++;
        current = current->next;
    }
    return (size);
}