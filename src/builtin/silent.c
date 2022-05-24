/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Silent builtins
*/

#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "shell.h"
#include "environment.h"
#include "my_arrays.h"
#include "my_math.h"
#include "my_string.h"

int silent_exit(env_t **env, char *const *args, shell_t *shell)
{
    size_t size = my_arraylen(args);

    (void) env;
    if (size == 1) {
        shell->exit = true;
        return (shell->ret);
    }
    if (size > 2 || args[1][0] <= '0' || args[1][0] >= '9')
        return (1);
    if (!my_is_number(args[1]))
        return (1);
    shell->exit = true;
    return (atoi(args[1]) % 256);
}

int silent_env(env_t **env, char *const *args, shell_t *shell)
{
    (void) env;
    (void) args;
    (void) shell;
    return (0);
}

int silent_setenv(env_t **env, char *const *args, shell_t *shell)
{
    size_t size = my_arraylen(args);

    (void) shell;
    if (size > 3 || (size >= 2 && !isalpha(args[1][0])))
        return (1);
    if (size != 1)
        return (set_variable(env, args[1], (size == 2 ? "" : args[2])));
    return (0);
}

int silent_unsetenv(env_t **env, char *const *args, shell_t *shell)
{
    size_t size = my_arraylen(args);

    (void) shell;
    if (size == 1)
        return (1);
    if (size == 2 && strcmp(args[1], "*") == 0) {
        destroy_env(*env);
        *env = NULL;
        return (0);
    }
    for (size_t i = 1; i < size; i++)
        remove_env_property(env, args[i]);
    return (0);
}

int silent_cd(env_t **env, char *const *args, shell_t *shell)
{
    int return_value = 1;
    size_t size = my_arraylen(args);
    char *path = getcwd(NULL, 0);

    (void) shell;
    if (path == NULL)
        return (return_value);
    if (size == 1)
        return_value = change_home_silently(env, path);
    else if (size == 2)
        return_value = handle_cd_silently(env, args[1], path);
    free(path);
    return (return_value);
}
