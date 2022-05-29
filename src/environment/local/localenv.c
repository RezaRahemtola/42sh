/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** General localenv functions
*/

#include <stdlib.h>
#include <string.h>
#include "my.h"
#include "shell.h"

const localenv_t *get_localenv_value(const localenv_t *list, const char *key)
{
    const localenv_t *current = list;

    while (current != NULL) {
        if (strcmp(current->key, key) == 0)
            return (current);
        current = current->next;
    }
    return (NULL);
}

void put_localenv_property(localenv_t **list, const char *key,
const char *value, bool readonly)
{
    localenv_t *env = malloc(sizeof(localenv_t));
    localenv_t *current = *list;

    if (env == NULL)
        return;
    env->key = strdup(key);
    env->value = strdup(value);
    env->readonly = readonly;
    env->next = NULL;
    if (*list == NULL) {
        *list = env;
    } else {
        while (current->next != NULL)
            current = current->next;
        current->next = env;
    }
}

void replace_localenv_value(localenv_t *list, const char *key,
const char *value, bool readonly)
{
    localenv_t *current = list;

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            free(current->value);
            current->value = strdup(value);
            current->readonly = readonly;
            return;
        }
        current = current->next;
    }
}

void remove_localenv_property(localenv_t **list, const char *key)
{
    localenv_t *current = *list;
    localenv_t *prev = *list;

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
