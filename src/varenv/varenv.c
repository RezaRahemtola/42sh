/*
** EPITECH PROJECT, 2021
** minishell2
** File description:
** Map management
*/

#include <stdlib.h>
#include <string.h>
#include "minishell.h"
#include "my.h"

varenv_t *varenv_get(varenv_t *list, const char *key)
{
    varenv_t *current = list;

    while (current != NULL) {
        if (strcmp(current->key, key) == 0)
            return (current);
        current = current->next;
    }
    return (NULL);
}

void varenv_put(varenv_t **list, const char *key, const char *value)
{
    varenv_t *env = malloc(sizeof(varenv_t));
    varenv_t *current = *list;

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

void varenv_replace(varenv_t *list, const char *key, const char *value)
{
    varenv_t *current = list;

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            free(current->value);
            current->value = strdup(value);
            return;
        }
        current = current->next;
    }
}

void varenv_remove(varenv_t **list, const char *key)
{
    varenv_t *current = *list;
    varenv_t *prev = *list;

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

int varenv_size(varenv_t *list)
{
    int size = 0;
    varenv_t *current = list;

    while (current != NULL) {
        size++;
        current = current->next;
    }
    return (size);
}
