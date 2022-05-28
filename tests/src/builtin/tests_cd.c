/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Unit tests for builtin cd
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "builtin.h"
#include "environment.h"

Test(cd, basic)
{
    char *const args[3] = {"cd", "/etc", NULL};
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    builtin_cd(&shell, args);
    cr_assert_eq(silent_cd(&shell, args), 0);
    cr_assert_not_null(shell.env);
    cr_assert_str_eq(shell.env->key, "PWD");
    cr_assert_str_eq(shell.env->value, "/etc");
    cr_assert_not_null(shell.env->next);
    cr_assert_str_eq(shell.env->next->key, "OLDPWD");
}

Test(cd, too_many_args, .init=cr_redirect_stderr)
{
    char *args[4] = {"cd", "a", "b", NULL};
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    builtin_cd(&shell, args);
    cr_assert_eq(silent_cd(&shell, args), 1);
    cr_assert_stderr_eq_str("cd: Too many arguments.\n");
}

Test(cd, fail_file, .init=cr_redirect_stderr)
{
    char *const args[3] = {"cd", "/etc/passwd", NULL};
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    builtin_cd(&shell, args);
    cr_assert_eq(silent_cd(&shell, args), 1);
    cr_assert_stderr_eq_str("/etc/passwd: Not a directory.\n");
}

Test(cd, fail_unexisting, .init=cr_redirect_stderr)
{
    char *const args[3] = {"cd", "/etcd", NULL};
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    builtin_cd(&shell, args);
    cr_assert_eq(silent_cd(&shell, args), 1);
    cr_assert_stderr_eq_str("/etcd: No such file or directory.\n");
}

Test(cd, home_unexisting, .init=cr_redirect_stderr)
{
    env_t *env = malloc(sizeof(env_t));
    char *const args[2] = {"cd", NULL};
    shell_t shell = {0, 0, env, NULL, NULL, NULL};

    shell.env->key = "YES";
    shell.env->value = "/";
    shell.env->next = NULL;
    builtin_cd(&shell, args);
    cr_assert_eq(silent_cd(&shell, args), 1);
    cr_assert_stderr_eq_str("cd: No home directory.\n");
    free(env);
}

Test(cd, prev)
{
    const env_t *oldpwd = NULL;
    char *const args[3] = {"cd", "/etc", NULL};
    char *const args2[3] = {"cd", "-", NULL};
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    builtin_cd(&shell, args);
    cr_assert_eq(silent_cd(&shell, args), 0);
    builtin_cd(&shell, args2);
    cr_assert_eq(silent_cd(&shell, args2), 0);
    cr_assert_not_null(get_env_value(shell.env, "PWD"));
    oldpwd = get_env_value(shell.env, "OLDPWD");
    cr_assert_not_null(oldpwd);
    cr_assert_str_eq(oldpwd->value, "/etc");
}

Test(cd, prev_usage, .init=cr_redirect_stderr)
{
    char *const args[3] = {"cd", "-a", NULL};
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    builtin_cd(&shell, args);
    cr_assert_eq(silent_cd(&shell, args), 1);
    cr_assert_stderr_eq_str("Usage: cd [-plvn][-|<dir>].\n");
}

Test(cd, prev_unexisting, .init=cr_redirect_stderr)
{
    char *const args[3] = {"cd", "-", NULL};
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    builtin_cd(&shell, args);
    cr_assert_eq(silent_cd(&shell, args), 1);
    cr_assert_stderr_eq_str(": No such file or directory.\n");
}

Test(cd, empty, .init=cr_redirect_stderr)
{
    char *const args[3] = {"cd", "", NULL};
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    builtin_cd(&shell, args);
    cr_assert_eq(silent_cd(&shell, args), 1);
    cr_assert_null(get_env_value(shell.env, "PWD"));
    cr_assert_null(get_env_value(shell.env, "OLDPWD"));
    cr_assert_stderr_eq_str(": No such file or directory.\n");
}
