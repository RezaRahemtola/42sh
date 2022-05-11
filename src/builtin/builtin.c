/*
** EPITECH PROJECT, 2021
** minishell2
** File description:
** Builtin commands
*/

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include "minishell.h"
#include "my_arrays.h"
#include "my_math.h"
#include "my_string.h"
#include "varenv.h"

void builtin_exit(__attribute__ ((unused)) varenv_t **env, char **args)
{
    size_t size = my_arraylen(args);

    if (size == 1)
        return;
    if (size > 2 || args[1][0] <= '0' || args[1][0] >= '9') {
        fprintf(stderr, "exit: Expression Syntax.\n");
        return;
    }
    if (!my_is_number(args[1])) {
        fprintf(stderr, "exit: Badly formed number.\n");
        return;
    }
}

void builtin_env(varenv_t **env, __attribute__ ((unused)) char **args)
{
    print_env(*env);
}

void builtin_setenv(varenv_t **env, char **args)
{
    size_t size = my_arraylen(args);

    if (size > 3) {
        fprintf(stderr, "setenv: Too many arguments.\n");
        return;
    }
    if (size >= 2 && !my_char_isalpha(args[1][0])) {
        fprintf(stderr, "setenv: Variable name must begin with a letter.\n");
        return;
    }
    if (size == 1)
        print_env(*env);
}

void builtin_unsetenv(__attribute__ ((unused)) varenv_t **env, char **args)
{
    if (my_arraylen(args) == 1)
        fprintf(stderr, "unsetenv: Too few arguments.\n");
}

void builtin_cd(varenv_t **env, char **args)
{
    size_t size = my_arraylen(args);
    char *path = getcwd(NULL, 0);

    if (path == NULL) {
        fprintf(stderr, "cd: %s.\n", strerror(errno));
        return;
    }
    if (size == 1)
        change_home(env);
    else if (size == 2)
        handle_cd(env, args[1]);
    else
        fprintf(stderr, "cd: Too many arguments.\n");
    free(path);
}
