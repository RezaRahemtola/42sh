/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Builtin commands
*/

#include <errno.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "environment.h"
#include "messages.h"
#include "my_arrays.h"
#include "my_math.h"
#include "my_string.h"
#include "shell.h"

void builtin_exit(__attribute__ ((unused)) shell_t *shell, char *const *args)
{
    size_t size = my_arraylen(args);

    if (size == 1)
        return;
    if (size > 2 || args[1][0] <= '0' || args[1][0] >= '9') {
        fprintf(stderr, "exit: %s\n", SYNTAX_ERROR);
        return;
    }
    if (!my_is_number(args[1]))
        fprintf(stderr, "exit: %s\n", NUMBER_ERROR);
}

void builtin_env(shell_t *shell, __attribute__ ((unused)) char *const *args)
{
    print_env(shell->env);
}

void builtin_setenv(shell_t *shell, char *const *args)
{
    size_t size = my_arraylen(args);

    if (size > 3) {
        fprintf(stderr, "setenv: %s\n", TOO_MANY_ARGS);
        return;
    }
    if (size >= 2 && !isalpha(args[1][0])) {
        fprintf(stderr, "setenv: %s\n", BEGIN_LETTER);
        return;
    }
    if (size >= 2 && !my_isalphanum_str(args[1])) {
        fprintf(stderr, "setenv: %s\n", NON_ALPHA);
        return;
    }
    if (size == 1)
        print_env(shell->env);
}

void builtin_unsetenv(shell_t *shell, char *const *args)
{
    (void) shell;
    if (my_arraylen(args) == 1)
        fprintf(stderr, "unsetenv: %s\n", TOO_FEW_ARGS);
}

void builtin_cd(shell_t *shell, char *const *args)
{
    size_t size = my_arraylen(args);
    char *path = getcwd(NULL, 0);

    if (path == NULL) {
        fprintf(stderr, "cd: %s.\n", strerror(errno));
        return;
    }
    if (size == 1)
        change_home(shell->env);
    else if (size == 2)
        handle_cd(shell->env, args[1]);
    else
        fprintf(stderr, "cd: %s\n", TOO_MANY_ARGS);
    free(path);
}
