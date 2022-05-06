/*
** EPITECH PROJECT, 2021
** minishell2
** File description:
** Map management
*/

#include <stdlib.h>
#include "minishell.h"
#include "my_string.h"
#include "my.h"

varenv_t *varenv_get(varenv_t *list, char const *key)
{
    varenv_t *current = list;

    while (current != NULL) {
        if (my_strcmp(current->key, key) == 0) {
            return (current);
        }
        current = current->next;
    }
    return (NULL);
}

void varenv_put(varenv_t **list, char *key, char *value)
{
    varenv_t *env = malloc(sizeof(varenv_t));
    varenv_t *current = *list;

    if (env == NULL) {
        return;
    }
    env->key = key;
    env->value = value;
    env->next = NULL;
    if (*list == NULL) {
        *list = env;
    } else {
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = env;
    }
}

void varenv_replace(varenv_t *list, char *key, char *value)
{
    varenv_t *current = list;

    while (current != NULL) {
        if (my_strcmp(current->key, key) == 0) {
            free(current->value);
            current->value = value;
            return;
        }
        current = current->next;
    }
}

void varenv_remove(varenv_t **list, char *key)
{
    varenv_t *current = *list;
    varenv_t *prev = *list;

    if (my_strcmp(current->key, key) == 0) {
        *list = current->next;
        my_free(3, current->key, current->value, current);
        return;
    }
    while (current != NULL) {
        if (my_strcmp(current->key, key) == 0) {
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
