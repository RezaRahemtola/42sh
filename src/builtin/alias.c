/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Alias builtin
*/

#include <stdio.h>
#include <string.h>
#include "environment.h"
#include "my_arrays.h"

static void set_alias(env_t **aliases, char *alias, char *command)
{
    const env_t *node = get_env_value(*aliases, alias);

    if (node == NULL) {
        put_env_property(aliases, alias, command);
        return;
    } else {
        replace_env_value(*aliases, alias, command);
    }
}

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
    bool not = false;
    size_t size = my_arraylen(args);

    (void) env;
    if (size == 1) {
        print_aliases(shell->aliases);
    } else if (size == 2) {
        print_alias(shell->aliases, args[1]);
    }
    if (size > 2) {
        not = strcmp("alias", args[1]) == 0 || strcmp("unalias", args[1]) == 0;
        if (not) {
            printf("%s: Too dangerous to alias that.\n", args[1]);
        }
    }
}

int silent_alias(env_t **env, char *const *args, shell_t *shell)
{
    bool not = false;
    size_t size = my_arraylen(args);

    if (size > 2) {
        not = strcmp("alias", args[1]) == 0 || strcmp("unalias", args[1]) == 0;
        if (!not)
            set_alias(&shell->aliases, args[1], args[2]);
    }
    (void) env;
    (void) shell;
    return (0);
}
