/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Unalias builtin
*/

#include <stdio.h>
#include <string.h>
#include "environment.h"
#include "my_arrays.h"

void builtin_unalias(__attribute__ ((unused)) env_t **env, char *const *args, \
shell_t *shell)
{
    (void) shell;
    if (my_arraylen(args) == 1)
        fprintf(stderr, "%s: Too few arguments.\n", args[0]);
}

int silent_unalias(env_t **env, char *const *args, shell_t *shell)
{
    size_t size = my_arraylen(args);

    (void) env;
    if (size == 1)
        return (1);
    if (size == 2 && strcmp(args[1], "*") == 0) {
        destroy_env(shell->aliases);
        shell->aliases = NULL;
        return (0);
    }
    for (size_t i = 1; i < size; i++)
        remove_env_property(&shell->aliases, args[i]);
    return (0);
}
