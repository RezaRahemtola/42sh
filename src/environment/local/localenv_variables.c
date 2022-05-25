/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Localenv variables management
*/

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "environment.h"
#include "my_string.h"

void add_localvar(localenv_t **env, const char *key, const char *value,
bool readonly)
{
    const localenv_t *var = get_localenv_value(*env, key);

    if (var == NULL)
        put_localenv_property(env, key, value, readonly);
    else
        replace_localenv_value(*env, key, value, readonly);
}

int set_localvar(localenv_t **env, const char *key,
const char *value, bool readonly)
{
    const char *alpha = "alphanumeric characters";

    if (my_isalphanum_str(key)) {
        add_localvar(env, key, value, readonly);
        return (0);
    }
    fprintf(stderr, "setenv: Variable name must contain %s.\n", alpha);
    return (1);
}
