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

static void set_alias(env_t **aliases, const char *alias, char *const *args,
size_t size)
{
    const env_t *node = get_env_value(*aliases, alias);
    char *joined = join_array(args, 2, size);

    if (joined == NULL)
        return;
    if (node == NULL)
        put_env_property(aliases, alias, joined);
    else
        replace_env_value(*aliases, alias, joined);
    free(joined);
}

static void print_alias(env_t *aliases, char *name)
{
    const env_t *alias = get_env_value(aliases, name);

    if (alias != NULL)
        printf("%s\n", alias->value);
}

static void print_aliases(env_t *aliases)
{
    bool mult = false;

    while (aliases != NULL) {
        mult = strchr(aliases->value, ' ') != NULL;
        if (mult)
            printf("%s\t(%s)\n", aliases->key, aliases->value);
        else
            printf("%s\t%s\n", aliases->key, aliases->value);
        aliases = aliases->next;
    }
}

void builtin_alias(shell_t *shell, char *const *args)
{
    bool not = false;
    size_t size = my_arraylen(args);

    if (size == 1)
        print_aliases(shell->aliases);
    else if (size == 2)
        print_alias(shell->aliases, args[1]);
    if (size > 2) {
        not = strcmp("alias", args[1]) == 0 || strcmp("unalias", args[1]) == 0;
        if (not)
            fprintf(stderr, "%s: Too dangerous to alias that.\n", args[1]);
    }
}

int silent_alias(shell_t *shell, char *const *args)
{
    bool not = false;
    size_t size = my_arraylen(args);

    if (size > 2) {
        not = strcmp("alias", args[1]) == 0 || strcmp("unalias", args[1]) == 0;
        if (not)
            return (1);
        set_alias(&shell->aliases, args[1], args, size - 2);
    }
    return (0);
}
