/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Unit tests for builtin local environment
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "environment.h"
#include "builtin.h"

Test(set, display_empty)
{
    char *const args[2] = {"set", NULL};
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    builtin_set(&shell, args);
    cr_assert_eq(silent_set(&shell, args), 0);
}

Test(set, display_empty_readonly)
{
    char *const args[3] = {"set", "-r", NULL};
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    builtin_set(&shell, args);
    cr_assert_eq(silent_set(&shell, args), 0);
}

Test(set, simple)
{
    char *const args[5] = {"set", "var", "=", "val", NULL};
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    builtin_set(&shell, args);
    cr_assert_eq(silent_set(&shell, args), 0);
    cr_assert_not_null(shell.localenv);
    cr_assert_str_eq(shell.localenv->key, "var");
    cr_assert_str_eq(shell.localenv->value, "val");
    cr_assert_eq(shell.localenv->readonly, false);
    cr_assert_null(shell.localenv->next);
}

Test(set, multiset)
{
    char *const args[4] = {"set", "var", "var2", NULL};
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    builtin_set(&shell, args);
    cr_assert_eq(silent_set(&shell, args), 0);
    cr_assert_not_null(shell.localenv);
    cr_assert_str_eq(shell.localenv->key, "var");
    cr_assert_str_eq(shell.localenv->value, "");
    cr_assert_eq(shell.localenv->readonly, false);
    cr_assert_not_null(shell.localenv->next);
}

Test(set, simple_readonly)
{
    char *const args[6] = {"set", "-r", "var", "=", "val", NULL};
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    builtin_set(&shell, args);
    cr_assert_eq(silent_set(&shell, args), 0);
    cr_assert_not_null(shell.localenv);
    cr_assert_str_eq(shell.localenv->key, "var");
    cr_assert_str_eq(shell.localenv->value, "val");
    cr_assert_eq(shell.localenv->readonly, true);
    cr_assert_null(shell.localenv->next);
}

Test(set, nonletter_start, .init=cr_redirect_stderr)
{
    char *const args[5] = {"set", "1var", "=", "val", NULL};
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    builtin_set(&shell, args);
    cr_assert_eq(silent_set(&shell, args), 1);
    cr_assert_null(shell.localenv);
    cr_assert_stderr_eq_str("set: Variable name must begin with a letter.\n");
}

Test(set, nonletter_start_multi, .init=cr_redirect_stderr)
{
    char *const args[4] = {"set", "var", "2var", NULL};
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    builtin_set(&shell, args);
    cr_assert_eq(silent_set(&shell, args), 1);
    cr_assert_stderr_eq_str("set: Variable name must begin with a letter.\n");
    cr_assert_not_null(shell.localenv);
    cr_assert_str_eq(shell.localenv->key, "var");
    cr_assert_str_eq(shell.localenv->value, "");
    cr_assert_eq(shell.localenv->readonly, false);
    cr_assert_null(shell.localenv->next);
}

Test(set, nonalphanum, .init=cr_redirect_stderr)
{
    char *const args[5] = {"set", "va+r", "=", "val", NULL};
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    builtin_set(&shell, args);
    cr_assert_eq(silent_set(&shell, args), 1);
    cr_assert_null(shell.localenv);
    cr_assert_stderr_eq_str("set: Variable name must contain alphanumeric characters.\n");
}

Test(set, nonalphanum_multi, .init=cr_redirect_stderr)
{
    char *const args[4] = {"set", "var", "va+r2", NULL};
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    builtin_set(&shell, args);
    cr_assert_eq(silent_set(&shell, args), 1);
    cr_assert_stderr_eq_str("set: Variable name must contain alphanumeric characters.\n");
    cr_assert_not_null(shell.localenv);
    cr_assert_str_eq(shell.localenv->key, "var");
    cr_assert_str_eq(shell.localenv->value, "");
    cr_assert_eq(shell.localenv->readonly, false);
    cr_assert_null(shell.localenv->next);
}

Test(set, reset_readonly, .init=cr_redirect_stderr)
{
    char *const args[6] = {"set", "-r", "var", "=", "val", NULL};
    char *const args2[5] = {"set", "var", "=", "val2", NULL};
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    builtin_set(&shell, args);
    cr_assert_eq(silent_set(&shell, args), 0);
    builtin_set(&shell, args2);
    cr_assert_eq(silent_set(&shell, args2), 1);
    cr_assert_stderr_eq_str("set: $var is read-only.\n");
    cr_assert_not_null(shell.localenv);
    cr_assert_str_eq(shell.localenv->key, "var");
    cr_assert_str_eq(shell.localenv->value, "val");
    cr_assert_eq(shell.localenv->readonly, true);
    cr_assert_null(shell.localenv->next);
}

Test(set, reset_readonly_multi, .init=cr_redirect_stderr)
{
    char *const args[5] = {"set", "-r", "var", "var2", NULL};
    char *const args2[5] = {"set", "var2", "=", "val2", NULL};
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    builtin_set(&shell, args);
    cr_assert_eq(silent_set(&shell, args), 0);
    builtin_set(&shell, args2);
    cr_assert_eq(silent_set(&shell, args2), 1);
    cr_assert_stderr_eq_str("set: $var2 is read-only.\n");
    cr_assert_not_null(shell.localenv);
    cr_assert_str_eq(shell.localenv->key, "var");
    cr_assert_str_eq(shell.localenv->value, "");
    cr_assert_eq(shell.localenv->readonly, true);
    cr_assert_not_null(shell.localenv->next);
    cr_assert_str_eq(shell.localenv->next->key, "var2");
    cr_assert_str_eq(shell.localenv->next->value, "");
    cr_assert_eq(shell.localenv->readonly, true);
    cr_assert_null(shell.localenv->next->next);
}

Test(unset, no_arg, .init=cr_redirect_stderr)
{
    char *const args[2] = {"unset", NULL};
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    builtin_unset(&shell, args);
    cr_assert_eq(silent_unset(&shell, args), 1);
    cr_assert_stderr_eq_str("unset: Too few arguments.\n");
}

Test(unset, unexisting_var)
{
    char *const args[3] = {"unset", "var", NULL};
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    builtin_unset(&shell, args);
    cr_assert_eq(silent_unset(&shell, args), 0);
}

Test(unset, unexisting_var_multi)
{
    char *const args[4] = {"unset", "var", "var2", NULL};
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    builtin_unset(&shell, args);
    cr_assert_eq(silent_unset(&shell, args), 0);
}

Test(unset, readonly, .init=cr_redirect_stderr)
{
    char *const args[6] = {"set", "-r", "var", "=", "val", NULL};
    char *const args2[3] = {"unset", "var", NULL};
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    builtin_set(&shell, args);
    cr_assert_eq(silent_set(&shell, args), 0);
    builtin_unset(&shell, args2);
    cr_assert_eq(silent_unset(&shell, args2), 1);
    cr_assert_stderr_eq_str("unset: $var is read-only.\n");
    cr_assert_not_null(shell.localenv);
    cr_assert_str_eq(shell.localenv->key, "var");
    cr_assert_str_eq(shell.localenv->value, "val");
    cr_assert_eq(shell.localenv->readonly, true);
    cr_assert_null(shell.localenv->next);
}
