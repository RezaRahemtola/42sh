/*
** EPITECH PROJECT, 2022
** minishell2
** File description:
** Silent builtins
*/

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "minishell.h"
#include "my_arrays.h"
#include "my_math.h"
#include "my_string.h"
#include "varenv.h"

int silent_exit(varenv_t **env, char **args, minishell_t *shell)
{
    int size = my_arraylen(args);

    (void) env;
    if (size == 1) {
        shell->exit = 1;
        return (-1);
    } else if (size > 2 || args[1][0] <= '0' || args[1][0] >= '9')
        return (1);
    if (!my_is_number(args[1]))
        return (1);
    shell->exit = 1;
    return (atoi(args[1]) % 256);
}

int silent_env(varenv_t **env, char **args, minishell_t *shell)
{
    (void) env;
    (void) args;
    (void) shell;
    return (0);
}

int silent_setenv(varenv_t **env, char **args, minishell_t *shell)
{
    int size = my_arraylen(args);

    (void) shell;
    if (size > 3 || (size >= 2 && !my_char_isalpha(args[1][0])))
        return (1);
    if (size != 1)
        return (set_variable(env, args[1], (size == 2 ? "" : args[2])));
    return (0);
}

int silent_unsetenv(varenv_t **env, char **args, minishell_t *shell)
{
    int size = my_arraylen(args);

    (void) shell;
    if (size == 1)
        return (1);
    if (size == 2 && strcmp(args[1], "*") == 0) {
        destroy_env(*env);
        *env = NULL;
        return (0);
    }
    for (int i = 1; i < size; i++)
        varenv_remove(env, args[i]);
    return (0);
}

int silent_cd(varenv_t **env, char **args, minishell_t *shell)
{
    int return_value;
    int size = my_arraylen(args);
    char *path = getcwd(NULL, 0);

    (void) shell;
    if (path == NULL)
        return (1);
    if (size == 1)
        return_value = change_home_silently(env, path);
    else if (size == 2)
        return_value = handle_cd_silently(env, args[1], path);
    else
        return_value = 1;
    free(path);
    return (return_value);
}
