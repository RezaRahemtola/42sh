/*
** EPITECH PROJECT, 2022
** minishell2
** File description:
** Silent builtins
*/

#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"
#include "my_arrays.h"
#include "my_math.h"
#include "my_string.h"
#include "varenv.h"

void silent_exit(varenv_t **env, char **args, minishell_t *shell)
{
    int size = my_arraylen(args);

    (void) env;
    if (size == 1) {
        shell->exit = 1;
        return;
    } else if (size > 2 || args[1][0] <= '0' || args[1][0] >= '9') {
        shell->ret = 1;
        return;
    }
    if (!my_is_number(args[1])) {
        shell->ret = 1;
        return;
    }
    shell->exit = 1;
    shell->ret = my_getnbr(args[1]) % 256;
}

void silent_env(varenv_t **env, char **args, minishell_t *shell)
{
    (void) env;
    (void) args;
    shell->ret = 0;
}

void silent_setenv(varenv_t **env, char **args, minishell_t *shell)
{
    int size = my_arraylen(args);

    if (size > 3) {
        shell->ret = 1;
    } else if (size == 1) {
        shell->ret = 0;
    } else {
        set_variable(env, args[1], (size == 2 ? "" : args[2]), shell);
        shell->ret = 0;
    }
}

void silent_unsetenv(varenv_t **env, char **args, minishell_t *shell)
{
    int size = my_arraylen(args);

    if (size == 1) {
        shell->ret = 1;
        return;
    } else if (size == 2 && my_strcmp(args[1], "*") == 0) {
        destroy_env(*env);
        *env = NULL;
        shell->ret = 0;
        return;
    }
    for (int i = 1; i < size; i++) {
        varenv_remove(env, args[i]);
    }
    shell->ret = 0;
}

void silent_cd(varenv_t **env, char **args, minishell_t *shell)
{
    int size = my_arraylen(args);
    char *path = getcwd(NULL, 0);

    if (path == NULL) {
        shell->ret = 1;
        return;
    }
    if (size == 1) {
        s_change_home(env, shell, path);
    } else if (size == 2) {
        s_handle_cd(env, args[1], shell, path);
    } else {
        shell->ret = 1;
    }
    free(path);
}
