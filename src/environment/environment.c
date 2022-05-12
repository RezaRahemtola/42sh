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

environment_t *get_env_value(environment_t *list, const char *key)
{
    environment_t *current = list;

    while (current != NULL) {
        if (strcmp(current->key, key) == 0)
            return (current);
        current = current->next;
    }
    return (NULL);
}

void put_env_property(environment_t **list, const char *key, const char *value)
{
    environment_t *env = malloc(sizeof(environment_t));
    environment_t *current = *list;

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

void replace_env_value(environment_t *list, const char *key, const char *value)
{
    environment_t *current = list;

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            free(current->value);
            current->value = strdup(value);
            return;
        }
        current = current->next;
    }
}

void remove_env_property(environment_t **list, const char *key)
{
    environment_t *current = *list;
    environment_t *prev = *list;

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

int get_env_size(environment_t *list)
{
    int size = 0;
    environment_t *current = list;

    while (current != NULL) {
        size++;
        current = current->next;
    }
    return (size);
}
