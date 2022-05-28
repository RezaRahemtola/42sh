/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Variables management
*/

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "builtin.h"
#include "environment.h"
#include "my_string.h"
#include "my.h"

char *env_value(shell_t *shell, char *name)
{
    const localenv_t *localenv = get_localenv_value(shell->localenv, name);
    const env_t *env = get_env_value(shell->env, name);

    if (localenv != NULL) {
        return (strdup(localenv->value));
    } else if (env != NULL) {
        return (strdup(env->value));
    } else {
        return (NULL);
    }
}

char *get_variable_name(char const *str, size_t start, size_t len)
{
    for (size_t i = start; i < len; i++) {
        if (!isalpha(str[i])) {
            return (my_substr_size(str, start, i, len));
        }
    }
    return (len == start ? strdup("") : my_substr_size(str, start, len, len));
}

static bool replace_value(command_t *command, char *name, char *value, size_t i)
{
    char *input = malloc(sizeof(char) * (strlen(value) + 2));
    char *replaced = NULL;

    if (input == NULL) {
        my_free(2, name, value);
        return (false);
    }
    strcpy(input, "$");
    strcat(input, name);
    replaced = my_strrep(command->args[i], input, value);
    if (replaced == NULL) {
        my_free(3, name, value, input);
        return (false);
    }
    replace_argument(command, i, replaced);
    my_free(3, name, value, input);
    return (true);
}

bool replace_var(command_t *command, shell_t *shell, size_t index, size_t i)
{
    size_t size = strlen(command->args[index]);
    char *name = get_variable_name(command->args[index], i + 1, size);
    char *value = NULL;

    if (name == NULL)
        return (false);
    if (strlen(name) == 0) {
        fprintf(stderr, "Illegal variable name.\n");
        free(name);
        return (false);
    }
    value = env_value(shell, name);
    if (value == NULL) {
        fprintf(stderr, "%s: Undefined variable.\n", name);
        free(name);
        return (false);
    }
    return (replace_value(command, name, value, index));
}
