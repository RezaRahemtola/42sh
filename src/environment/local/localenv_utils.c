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
    while (env != NULL) {
        printf("%s\t%s\n", env->key, env->value);
        env = env->next;
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
