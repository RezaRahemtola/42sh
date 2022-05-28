/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Home value replacements
*/

#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "builtin.h"
#include "environment.h"
#include "messages.h"
#include "my_string.h"

static char *get_user(char *argument)
{
    size_t size = strlen(argument);

    if (size == 1)
        return (NULL);
    for (size_t i = 1; i < size; i++) {
        if (argument[i] == '/') {
            return (i > 1 ? my_substr_size(argument, 1, i, size) : NULL);
        }
    }
    return (my_substr_size(argument, 1, size, size));
}

static bool replace_user_in_argument(command_t *command, size_t i, char *user,
char *path)
{
    char *usr = malloc(sizeof(char) * (strlen(user) + 2));
    char *replaced = NULL;

    if (usr == NULL)
        return (false);
    strcpy(usr, "~");
    strcat(usr, user);
    replaced = my_strrep(command->args[i], usr, path);
    free(usr);
    replace_argument(command, i, replaced);
    return (true);
}

static bool replace_home_user(command_t *command, char *user, size_t i)
{
    bool out = false;
    char *path = NULL;

    if (getpwnam(user) == NULL) {
        fprintf(stderr, "%s %s\n", NO_USER, user);
        return (false);
    }
    path = malloc(sizeof(char) * (strlen(user) + 7));
    if (path == NULL)
        return (false);
    strcpy(path, "/home/");
    strcat(path, user);
    out = replace_user_in_argument(command, i, user, path);
    free(path);
    return (out);
}

static bool replace_home_value(command_t *command, shell_t *shell, size_t i)
{
    const localenv_t *home = get_localenv_value(shell->localenv, "home");
    char *replaced = NULL;

    if (home == NULL) {
        fprintf(stderr, "%s\n", NO_HOME_VARIABLE);
        return (false);
    }
    replaced = my_strrep(command->args[i], "~", home->value);
    if (replaced == NULL)
        return (false);
    replace_argument(command, i, replaced);
    return (true);
}

bool replace_home(command_t *command, shell_t *shell, size_t size)
{
    bool out = true;
    char *user = NULL;

    for (size_t i = 0; i < size && out; i++) {
        if (strlen(command->args[i]) == 0 || command->args[i][0] != '~')
            continue;
        user = get_user(command->args[i]);
        if (user == NULL && !replace_home_value(command, shell, i))
            return (false);
        if (user != NULL) {
            out = replace_home_user(command, user, i);
            free(user);
        }
    }
    return (out);
}
