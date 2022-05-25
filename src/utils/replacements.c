/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Values replacements
*/

#include <stdlib.h>
#include <string.h>
#include "my_arrays.h"
#include "my_string.h"
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
    char *input = NULL;
    command_t *current = commands;
    env_t *alias = NULL;

    while (current != NULL) {
        first = current->args[0];
        alias = (first == NULL ? NULL : get_alias(first, aliases));
        if (alias != NULL) {
            free(current->path);
            my_free_arrays(1, current->args);
            input = current->input;
            current->input = my_strrep(input, alias->key, alias->value);
            current->args = my_strsplit_many(current->input, " \t");
            current->path = find_command(env, current->args[0]);
            free(input);
        }
        current = current->next;
    }
}
