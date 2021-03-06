/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Functions to check if a set call is valid
*/

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "my_arrays.h"
#include "my_string.h"
#include "messages.h"
#include "types.h"

bool is_localvar_readonly(localenv_t *env, const char *key)
{
    while (env != NULL) {
        if (strcmp(env->key, key) == 0)
            return (env->readonly);
        env = env->next;
    }
    return (false);
}

bool is_valid_localvar(const char *var, localenv_t *env, bool print)
{
    if (!isalpha(var[0])) {
        if (print)
            fprintf(stderr, "set: Variable name must begin with a letter.\n");
        return (false);
    }
    if (!my_isalphanum_str(var)) {
        if (print)
            fprintf(stderr, "set: %s\n", NON_ALPHA);
        return (false);
    }
    if (is_localvar_readonly(env, var)) {
        if (print)
            fprintf(stderr, "set: $%s is read-only.\n", var);
        return (false);
    }
    return (true);
}
