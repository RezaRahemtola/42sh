/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Values replacements
*/

#include <stdlib.h>
#include <string.h>
#include "shell.h"

static env_t *get_alias(char *command, env_t *aliases)
{
    env_t *current = aliases;

    while (current != NULL) {
        if (strcmp(current->key, command) == 0) {
            return current;
        }
        current = current->next;
    }
    return (NULL);
}

void replace_aliases(command_t *commands, env_t *aliases, env_t *env)
{
    char *first = NULL;
    command_t *current = commands;
    env_t *alias = NULL;

    while (current != NULL) {
        first = current->args[0];
        alias = (first == NULL ? NULL : get_alias(first, aliases));
        if (alias != NULL) {
            free(current->args[0]);
            free(current->path);
            current->args[0] = strdup(alias->value);
            current->path = find_command(env, current->args[0]);
        }
        current = current->next;
    }
}
