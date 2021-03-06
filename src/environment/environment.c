/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** General environment functions
*/

#include <stdlib.h>
#include <string.h>
#include "my.h"
#include "shell.h"

const env_t *get_env_value(const env_t *list, const char *key)
{
    while (list != NULL) {
        if (strcmp(list->key, key) == 0)
            return (list);
        list = list->next;
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
    if (*list == NULL) {
        *list = env;
    } else {
        while (current->next != NULL)
            current = current->next;
        current->next = env;
    }
}

void replace_env_value(env_t *list, const char *key, const char *value)
{
    while (list != NULL) {
        if (strcmp(list->key, key) == 0) {
            free(list->value);
            list->value = strdup(value);
            return;
        }
        list = list->next;
    }
}

void remove_env_property(env_t **list, const char *key)
{
    env_t *current = *list;
    env_t *prev = *list;

    if (current != NULL && strcmp(current->key, key) == 0) {
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

size_t get_env_size(const env_t *list)
{
    size_t size = 0;

    for (; list != NULL; size++)
        list = list->next;
    return (size);
}
