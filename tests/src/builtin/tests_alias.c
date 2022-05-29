/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Unit tests for aliases
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "shell.h"
#include "builtin.h"

Test(alias, no_arg)
{
    char *const args[2] = {"alias", NULL};
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    builtin_alias(&shell, args);
    cr_assert_eq(silent_alias(&shell, args), 0);
}

Test(alias, set_forbidden_alias, .init=cr_redirect_stderr)
{
    char *const args[4] = {"alias", "alias", "value", NULL};
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    builtin_alias(&shell, args);
    cr_assert_eq(silent_alias(&shell, args), 1);
    cr_assert_stderr_eq_str("alias: Too dangerous to alias that.\n");
}

Test(alias, set_forbidden_unalias, .init=cr_redirect_stderr)
{
    char *const args[4] = {"alias", "unalias", "value", NULL};
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    builtin_alias(&shell, args);
    cr_assert_eq(silent_alias(&shell, args), 1);
    cr_assert_stderr_eq_str("unalias: Too dangerous to alias that.\n");
}

Test(alias, set_simple, .init=cr_redirect_stdout)
{
    const char *input = "alias myalias value ; alias | grep myalias\n";
    env_t *env = malloc(sizeof(env_t));
    shell_t shell = {0, 0, env, NULL, NULL, NULL};

    env->key = "PATH";
    env->value = "/bin";
    handle_input(input, &shell);
    cr_assert_stdout_eq_str("myalias\tvalue\n");
    free(env);
}

Test(alias, set_multiple, .init=cr_redirect_stdout)
{
    const char *input = "alias myalias val1 val2 val3 ; alias | grep myalias\n";
    env_t *env = malloc(sizeof(env_t));
    shell_t shell = {0, 0, env, NULL, NULL, NULL};

    env->key = "PATH";
    env->value = "/bin";
    handle_input(input, &shell);
    cr_assert_stdout_eq_str("myalias\t(val1 val2 val3)\n");
    free(env);
}

Test(unalias, no_arg, .init=cr_redirect_stderr)
{
    char *const args[2] = {"unalias", NULL};
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    builtin_unalias(&shell, args);
    cr_assert_eq(silent_unalias(&shell, args), 1);
    cr_assert_stderr_eq_str("unalias: Too few arguments.\n");
}

Test(unalias, non_existing_alias)
{
    char *const args[3] = {"unalias", "notanalias", NULL};
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    builtin_unalias(&shell, args);
    cr_assert_eq(silent_unalias(&shell, args), 0);
}

Test(unalias, multiple_non_existing)
{
    char *const args[4] = {"unalias", "notanalias", "notanalias2", NULL};
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    builtin_unalias(&shell, args);
    cr_assert_eq(silent_unalias(&shell, args), 0);
}

Test(unalias, all, .init=cr_redirect_stderr)
{
    char *const args[4] = {"alias", "myalias", "value", NULL};
    char *const args2[3] = {"unalias", "*", NULL};
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    builtin_alias(&shell, args);
    cr_assert_eq(silent_alias(&shell, args), 0);
    cr_assert_not_null(shell.aliases);
    builtin_unalias(&shell, args2);
    cr_assert_eq(silent_unalias(&shell, args2), 0);
    cr_assert_null(shell.aliases);
}

Test(unalias, all_non_existing, .init=cr_redirect_stderr)
{
    char *const args[3] = {"unalias", "*", NULL};
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    builtin_unalias(&shell, args);
    cr_assert_eq(silent_unalias(&shell, args), 0);
}
