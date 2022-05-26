/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Unit tests for builtin exit
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "builtin.h"

Test(exit, simple)
{
    char *const args[2] = {"exit", NULL};
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    builtin_exit(&shell, args);
    silent_exit(&shell, args);
    cr_assert_eq(shell.ret, 0);
    cr_assert_eq(shell.exit, 1);
}

Test(exit, modulo)
{
    int ret = 0;
    char *const args[3] = {"exit", "258", NULL};
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    ret = silent_exit(&shell, args);
    cr_assert_eq(ret, 2);
    cr_assert_eq(shell.exit, 1);
}

Test(exit, wrong_arg, .init=cr_redirect_stderr)
{
    int ret = 0;
    char *const args[3] = {"exit", "salut", NULL};
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    builtin_exit(&shell, args);
    ret = silent_exit(&shell, args);
    cr_assert_stderr_eq_str("exit: Expression Syntax.\n");
    cr_assert_eq(ret, 1);
    cr_assert_eq(shell.exit, 0);
}

Test(exit, wrong_arg_2, .init=cr_redirect_stderr)
{
    int ret = 0;
    char *const args[3] = {"exit", "!17", NULL};
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    builtin_exit(&shell, args);
    ret = silent_exit(&shell, args);
    cr_assert_stderr_eq_str("exit: Expression Syntax.\n");
    cr_assert_eq(ret, 1);
    cr_assert_eq(shell.exit, 0);
}

Test(exit, not_a_number, .init=cr_redirect_stderr)
{
    int ret = 0;
    char *const args[3] = {"exit", "1a"};
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    builtin_exit(&shell, args);
    ret = silent_exit(&shell, args);
    cr_assert_stderr_eq_str("exit: Badly formed number.\n");
    cr_assert_eq(ret, 1);
    cr_assert_eq(shell.exit, 0);
}

Test(exit, too_many_args, .init=cr_redirect_stderr)
{
    int ret = 0;
    char *const args[4] = {"exit", "salut", "bonsoir", NULL};
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    builtin_exit(&shell, args);
    ret = silent_exit(&shell, args);
    cr_assert_stderr_eq_str("exit: Expression Syntax.\n");
    cr_assert_eq(ret, 1);
    cr_assert_eq(shell.exit, 0);
}
