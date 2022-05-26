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
    int ret = 0;
    char *const args[3] = {"cd", "/etc", NULL};
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    builtin_cd(&shell, args);
    ret = silent_cd(&shell, args);
    cr_assert_not_null(shell.env);
    cr_assert_str_eq(shell.env->key, "PWD");
    cr_assert_str_eq(shell.env->value, "/etc");
    cr_assert_not_null(shell.env->next);
    cr_assert_str_eq(shell.env->next->key, "OLDPWD");
    cr_assert_eq(ret, 0);
}

Test(cd, too_many_args, .init=cr_redirect_stderr)
{
    int ret = 0;
    char *args[4] = {"cd", "a", "b", NULL};
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    builtin_cd(&shell, args);
    ret = silent_cd(&shell, args);
    cr_assert_eq(ret, 1);
    cr_assert_stderr_eq_str("cd: Too many arguments.\n");
}

Test(cd, fail_file, .init=cr_redirect_stderr)
{
    int ret = 0;
    char *const args[3] = {"cd", "/etc/passwd", NULL};
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    builtin_cd(&shell, args);
    ret = silent_cd(&shell, args);
    cr_assert_eq(ret, 1);
    cr_assert_stderr_eq_str("/etc/passwd: Not a directory.\n");
}

Test(cd, fail_unexisting, .init=cr_redirect_stderr)
{
    int ret = 0;
    char *const args[3] = {"cd", "/etcd", NULL};
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    builtin_cd(&shell, args);
    ret = silent_cd(&shell, args);
    cr_assert_eq(ret, 1);
    cr_assert_stderr_eq_str("/etcd: No such file or directory.\n");
}

Test(cd, home_unexisting, .init=cr_redirect_stderr)
{
    int ret = 0;
    env_t *env = malloc(sizeof(env_t));
    char *const args[2] = {"cd", NULL};
    shell_t shell = {0, 0, env, NULL, NULL, NULL};

    shell.env->key = "YES";
    shell.env->value = "/";
    shell.env->next = NULL;
    builtin_cd(&shell, args);
    ret = silent_cd(&shell, args);
    cr_assert_stderr_eq_str("cd: No home directory.\n");
    cr_assert_eq(ret, 1);
    free(env);
}

Test(cd, home_valid)
{
    env_t *env = malloc(sizeof(env_t));
    char *const args[3] = {"cd", "~"};
    shell_t shell = {0, 0, env, NULL, NULL, NULL};

    shell.env->key = "HOME";
    shell.env->value = "/";
    shell.env->next = NULL;
    builtin_cd(&shell, args);
    silent_cd(&shell, args);
    cr_assert_eq(shell.ret, 0);
    free(env);
}

Test(cd, home_invalid, .init=cr_redirect_stderr)
{
    int ret = 0;
    env_t *env = malloc(sizeof(env_t));
    char *const args[3] = {"cd", "~"};
    shell_t shell = {0, 0, env, NULL, NULL, NULL};

    shell.env->key = "HOME";
    shell.env->value = "/etc/fstab";
    shell.env->next = NULL;
    builtin_cd(&shell, args);
    ret = silent_cd(&shell, args);
    cr_assert_stderr_eq_str("cd: Can't change to home directory.\n");
    cr_assert_eq(ret, 1);
    free(env);
}

Test(cd, home_append, .init=cr_redirect_stderr)
{
    env_t *env = malloc(sizeof(env_t));
    char *const args[3] = {"cd", "~/etc", NULL};
    shell_t shell = {0, 0, env, NULL, NULL, NULL};

    env->key = "YES";
    env->value = "/";
    env->next = NULL;
    builtin_cd(&shell, args);
    cr_assert_eq(silent_cd(&shell, args), 1);
    env->key = "HOME";
    builtin_cd(&shell, args);
    cr_assert_eq(silent_cd(&shell, args), 0);
    cr_assert_stderr_eq_str("No $home variable set.\n");
    free(env);
}

Test(cd, prev)
{
    const env_t *pwd = NULL;
    const env_t *oldpwd = NULL;
    char *const args[3] = {"cd", "/etc", NULL};
    char *const args2[3] = {"cd", "-", NULL};
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    builtin_cd(&shell, args);
    cr_assert_eq(silent_cd(&shell, args), 0);
    builtin_cd(&shell, args2);
    cr_assert_eq(silent_cd(&shell, args2), 0);
    pwd = get_env_value(shell.env, "PWD");
    oldpwd = get_env_value(shell.env, "OLDPWD");
    cr_assert_not_null(pwd);
    cr_assert_not_null(oldpwd);
    cr_assert_str_eq(oldpwd->value, "/etc");
}

Test(cd, prev_usage, .init=cr_redirect_stderr)
{
    int ret = 0;
    char *const args[3] = {"cd", "-a", NULL};
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    builtin_cd(&shell, args);
    ret = silent_cd(&shell, args);
    cr_assert_stderr_eq_str("Usage: cd [-plvn][-|<dir>].\n");
    cr_assert_eq(ret, 1);
}

Test(cd, prev_unexisting, .init=cr_redirect_stderr)
{
    int ret = 0;
    char *const args[3] = {"cd", "-", NULL};
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    builtin_cd(&shell, args);
    ret = silent_cd(&shell, args);
    cr_assert_stderr_eq_str(": No such file or directory.\n");
    cr_assert_eq(ret, 1);
}

Test(cd, empty, .init=cr_redirect_stderr)
{
    int ret = 0;
    env_t *env = NULL;
    const env_t *pwd = NULL;
    const env_t *oldpwd = NULL;
    char *const args[3] = {"cd", "", NULL};
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    builtin_cd(&shell, args);
    ret = silent_cd(&shell, args);
    cr_assert_eq(ret, 1);
    pwd = get_env_value(env, "PWD");
    oldpwd = get_env_value(env, "OLDPWD");
    cr_assert_null(pwd);
    cr_assert_null(oldpwd);
    cr_assert_stderr_eq_str(": No such file or directory.\n");
}
