/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Alias builtin
*/

#include <stdio.h>
#include "environment.h"
#include "my_arrays.h"

static void print_alias(env_t *aliases, char *name)
{
    const env_t *alias = get_env_value(aliases, name);

    if (alias != NULL) {
        printf("%s\n", alias->value);
    }
}

static void print_aliases(env_t *aliases)
{
    env_t *current = aliases;

    while (current != NULL) {
        printf("%s\t%s\n", current->key, current->value);
        current = current->next;
    }
}

void builtin_alias(env_t **env, char *const *args, shell_t *shell)
{
    (void) env;
    size_t size = my_arraylen(args);

    if (size == 0) {
        print_aliases(shell->aliases);
    } else if (size == 1) {
        print_alias(shell->aliases, args[0]);
    }
}

int silent_alias(env_t **env, char *const *args, shell_t *shell)
{
    (void) env;
    (void) args;
    (void) shell;
    return (0);
}
