/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Utils function for localenv
*/

#include <stdio.h>
#include <stdlib.h>
#include "environment.h"

void print_localenv(const localenv_t *env)
{
    const localenv_t *current = env;

    while (current != NULL) {
        printf("%s=%s\n", current->key, current->value);
        current = current->next;
    }
}

void destroy_localenv(localenv_t *env)
{
    localenv_t *current = env;
    localenv_t *tmp = NULL;

    while (current != NULL) {
        tmp = current->next;
        free(current->key);
        free(current->value);
        free(current);
        current = tmp;
    }
}
