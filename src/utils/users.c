/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Users
*/

#include <pwd.h>
#include <string.h>
#include "my_string.h"

char *get_user(char *argument)
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

bool user_exists(char *name)
{
    struct passwd *user = getpwnam(name);

    return (user != NULL);
}
