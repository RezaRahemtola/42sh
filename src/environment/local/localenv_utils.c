/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Utils function for localenv
*/

#include <stddef.h>
#include "environment.h"

void print_localenv(const list_t *env)
{
    const env_t *elem = NULL;

    while (env != NULL) {
        elem = env->data;
        printf("%s=%s\n", elem->key, elem->value);
        elem = elem->next;
    }
}
