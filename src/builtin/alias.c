/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Alias builtin
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "environment.h"
#include "my_arrays.h"
#include "shell.h"

static void set_alias(env_t **aliases, char *alias, char *const *args, \
size_t size)
{
    const env_t *node = get_env_value(*aliases, alias);
    char *joined = join_array(args, 2, size);

    if (joined == NULL) {
        return;
    }
    if (node == NULL) {
        put_env_property(aliases, alias, joined);
    } else {
        replace_env_value(*aliases, alias, joined);
    }
    free(joined);
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
    bool mult = false;
    env_t *current = aliases;

    while (current != NULL) {
        mult = strchr(current->value, ' ') != NULL;
        if (mult)
            printf("%s\t(%s)\n", current->key, current->value);
        else
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
            set_alias(&shell->aliases, args[1], args, size - 2);
    }
    (void) env;
    (void) shell;
    return (0);
}
