/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Unit tests on builtins
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "builtin.h"
#include "my_string.h"
#include "environment.h"

Test(builtin, command_check)
{
    bool valid = is_builtin("cd");
    bool invalid = is_builtin("ls");

    cr_assert_eq(valid, true);
    cr_assert_eq(invalid, false);
}

Test(builtin, exit)
{
    environment_t *env = NULL;
    char *args[2] = {"exit", NULL};
    shell_t shell = {0, 0};

    silent_exit(&env, args, &shell);
    cr_assert_eq(shell.ret, 0);
    cr_assert_eq(shell.exit, 1);
}

Test(builtin, exit_modulo)
{
    int ret = 0;
    environment_t *env = NULL;
    char *args[3] = {"exit", "258", NULL};
    shell_t shell = {0, 0};

    ret = silent_exit(&env, args, &shell);
    cr_assert_eq(ret, 2);
    cr_assert_eq(shell.exit, 1);
}

Test(builtin, exit_wrong_arg, .init=cr_redirect_stderr)
{
    int ret = 0;
    environment_t *env = NULL;
    char *args[3] = {"exit", "salut", NULL};
    shell_t shell = {0, 0};

    builtin_exit(&env, args);
    ret = silent_exit(&env, args, &shell);
    cr_assert_stderr_eq_str("exit: Expression Syntax.\n");
    cr_assert_eq(ret, 1);
    cr_assert_eq(shell.exit, 0);
}

Test(builtin, exit_wrong_arg_2, .init=cr_redirect_stderr)
{
    int ret = 0;
    environment_t *env = NULL;
    char *args[3] = {"exit", "!17", NULL};
    shell_t shell = {0, 0};

    builtin_exit(&env, args);
    ret = silent_exit(&env, args, &shell);
    cr_assert_stderr_eq_str("exit: Expression Syntax.\n");
    cr_assert_eq(ret, 1);
    cr_assert_eq(shell.exit, 0);
}

Test(builtin, exit_not_a_number, .init=cr_redirect_stderr)
{
    int ret = 0;
    environment_t *env = NULL;
    char *args[3] = {"exit", "1a"};
    shell_t shell = {0, 0};

    builtin_exit(&env, args);
    ret = silent_exit(&env, args, &shell);
    cr_assert_stderr_eq_str("exit: Badly formed number.\n");
    cr_assert_eq(ret, 1);
    cr_assert_eq(shell.exit, 0);
}

Test(builtin, exit_too_many_args, .init=cr_redirect_stderr)
{
    int ret = 0;
    environment_t *env = NULL;
    char *args[4] = {"exit", "salut", "bonsoir", NULL};
    shell_t shell = {0, 0};

    builtin_exit(&env, args);
    ret = silent_exit(&env, args, &shell);
    cr_assert_stderr_eq_str("exit: Expression Syntax.\n");
    cr_assert_eq(ret, 1);
    cr_assert_eq(shell.exit, 0);
}

Test(builtin, env, .init=cr_redirect_stdout)
{
    environment_t path = {"PATH", "/usr/bin:/bin", NULL};
    environment_t *env[2] = {&path, NULL};
    char *args[3] = {"env", NULL};
    shell_t shell = {0, 0};

    setbuf(stdout, NULL);
    builtin_env(env, args);
    cr_assert_stdout_eq_str("PATH=/usr/bin:/bin\n");
    cr_assert_eq(shell.ret, 0);
}

Test(builtin, setenv_set)
{
    environment_t path = {"PATH", strdup("/usr/bin:/bin"), NULL};
    environment_t *env[2] = {&path, NULL};
    char *args[4] = {"setenv", "PATH", "/etc", NULL};
    shell_t shell = {0, 0};

    silent_setenv(env, args, &shell);
    cr_assert_str_eq(path.value, "/etc");
    cr_assert_eq(shell.ret, 0);
}

Test(builtin, setenv_print, .init=cr_redirect_stdout)
{
    environment_t path = {"PATH", strdup("/usr/bin:/bin"), NULL};
    environment_t *env[2] = {&path, NULL};
    char *args[2] = {"setenv", NULL};
    shell_t shell = {0, 0};

    setbuf(stdout, NULL);
    builtin_setenv(env, args);
    silent_setenv(env, args, &shell);
    cr_assert_str_eq(path.value, "/usr/bin:/bin");
    cr_assert_eq(shell.ret, 0);
    cr_assert_stdout_eq_str("PATH=/usr/bin:/bin\n");
}

Test(builtin, setenv_alphanumeric, .init=cr_redirect_stderr)
{
    environment_t *env = NULL;
    char *args[3] = {"setenv", "PATH=", NULL};
    shell_t shell = {0, 0};

    builtin_setenv(&env, args);
    silent_setenv(&env, args, &shell);
    cr_assert_null(env);
    cr_assert_stderr_eq_str(
        "setenv: Variable name must contain alphanumeric characters.\n");
}

Test(builtin, setenv_too_many_args, .init=cr_redirect_stderr)
{
    int ret = 0;
    environment_t *env = NULL;
    char *args[5] = {"setenv", "PATH", "key", "value", NULL};
    shell_t shell = {0, 0};

    builtin_setenv(&env, args);
    ret = silent_setenv(&env, args, &shell);
    cr_assert_null(env);
    cr_assert_stderr_eq_str("setenv: Too many arguments.\n");
    cr_assert_eq(ret, 1);
}

Test(builtin, unsetenv, .init=cr_redirect_stderr)
{
    int ret = 0;
    int ret2 = 0;
    environment_t *env = malloc(sizeof(environment_t));
    environment_t *path = malloc(sizeof(environment_t));
    char *args[2] = {"unsetenv", NULL};
    char *args2[3] = {"unsetenv", "PATH", NULL};
    shell_t shell = {0, 0};
    shell_t shell2 = {0, 0};

    env->key = "HOME";
    env->value = "/home";
    env->next = path;
    path->key = strdup("PATH");
    path->value = strdup("/usr");
    path->next = NULL;
    builtin_unsetenv(&env, args);
    builtin_unsetenv(&env, args2);
    ret = silent_unsetenv(&env, args, &shell);
    ret2 = silent_unsetenv(&env, args2, &shell2);
    cr_assert_null(env->next);
    cr_assert_eq(ret, 1);
    cr_assert_eq(ret2, 0);
    cr_assert_stderr_eq_str("unsetenv: Too few arguments.\n");
}

Test(builtin, unsetenv_all, .init=cr_redirect_stderr)
{
    environment_t *env = malloc(sizeof(environment_t));
    environment_t *path = malloc(sizeof(environment_t));
    char *args[3] = {"unsetenv", "*", NULL};
    shell_t shell = {0, 0};

    env->key = strdup("HOME");
    env->value = strdup("/home");
    env->next = path;
    path->key = strdup("PATH");
    path->value = strdup("/usr");
    path->next = NULL;
    builtin_unsetenv(&env, args);
    silent_unsetenv(&env, args, &shell);
    cr_assert_null(env);
    cr_assert_eq(shell.ret, 0);
}

Test(builtin, unsetenv_all_error, .init=cr_redirect_stderr)
{
    environment_t *env = malloc(sizeof(environment_t));
    environment_t *path = malloc(sizeof(environment_t));
    char *args[4] = {"unsetenv", "*", "bonsoir", NULL};
    shell_t shell = {0, 0};

    env->key = strdup("HOME");
    env->value = strdup("/home");
    env->next = path;
    path->key = strdup("PATH");
    path->value = strdup("/usr");
    path->next = NULL;
    builtin_unsetenv(&env, args);
    silent_unsetenv(&env, args, &shell);
    cr_assert_not_null(env);
    cr_assert_eq(shell.ret, 0);
}

Test(builtin, cd_basic, .init=cr_redirect_stderr)
{
    int ret = 0;
    int ret2 = 0;
    environment_t *env = NULL;
    char *args[3] = {"cd", "/etc", NULL};
    char *args2[4] = {"cd", "a", "b", NULL};
    shell_t shell = {0, 0};
    shell_t shell2 = {0, 0};

    builtin_cd(&env, args);
    builtin_cd(&env, args2);
    ret = silent_cd(&env, args, &shell);
    ret2 = silent_cd(&env, args2, &shell2);
    cr_assert_not_null(env);
    cr_assert_str_eq(env->key, "PWD");
    cr_assert_str_eq(env->value, "/etc");
    cr_assert_not_null(env->next);
    cr_assert_str_eq(env->next->key, "OLDPWD");
    cr_assert_eq(ret, 0);
    cr_assert_stderr_eq_str("cd: Too many arguments.\n");
    cr_assert_eq(ret2, 1);
}

Test(builtin, cd_fail, .init=cr_redirect_stderr)
{
    int ret = 0;
    int ret2 = 0;
    environment_t *env = NULL;
    char *args[3] = {"cd", "/etc/passwd", NULL};
    char *args2[3] = {"cd", "/etcd", NULL};
    shell_t shell = {0, 0};
    shell_t shell2 = {0, 0};

    builtin_cd(&env, args);
    builtin_cd(&env, args2);
    ret = silent_cd(&env, args, &shell);
    ret2 = silent_cd(&env, args2, &shell2);
    cr_assert_stderr_eq_str(
        "/etc/passwd: Not a directory.\n/etcd: No such file or directory.\n");
    cr_assert_eq(ret, 1);
    cr_assert_eq(ret2, 1);
}

Test(builtin, cd_home_unexisting, .init=cr_redirect_stderr)
{
    int ret = 0;
    environment_t *env = malloc(sizeof(environment_t));
    char *args[2] = {"cd", NULL};
    shell_t shell = {0, 0};

    env->key = "YES";
    env->value = "/";
    env->next = NULL;
    builtin_cd(&env, args);
    ret = silent_cd(&env, args, &shell);
    cr_assert_stderr_eq_str("cd: No home directory.\n");
    cr_assert_eq(ret, 1);
}

Test(builtin, cd_home_valid)
{
    environment_t *env = malloc(sizeof(environment_t));
    char *args[3] = {"cd", "~"};
    shell_t shell = {0, 0};

    env->key = "HOME";
    env->value = "/";
    env->next = NULL;
    builtin_cd(&env, args);
    silent_cd(&env, args, &shell);
    cr_assert_eq(shell.ret, 0);
}

Test(builtin, cd_home_invalid, .init=cr_redirect_stderr)
{
    int ret = 0;
    environment_t *env = malloc(sizeof(environment_t));
    char *args[3] = {"cd", "~"};
    shell_t shell = {0, 0};

    env->key = "HOME";
    env->value = "/etc/fstab";
    env->next = NULL;
    builtin_cd(&env, args);
    ret = silent_cd(&env, args, &shell);
    cr_assert_stderr_eq_str("cd: Can't change to home directory.\n");
    cr_assert_eq(ret, 1);
}

Test(builtin, cd_home_append, .init=cr_redirect_stderr)
{
    int ret = 0;
    int ret2 = 0;
    environment_t *env = malloc(sizeof(environment_t));
    char *args[3] = {"cd", "~/etc", NULL};
    shell_t shell = {0, 0};
    shell_t shell2 = {0, 0};

    env->key = "YES";
    env->value = "/";
    env->next = NULL;
    builtin_cd(&env, args);
    ret = silent_cd(&env, args, &shell);
    env->key = "HOME";
    builtin_cd(&env, args);
    ret2 = silent_cd(&env, args, &shell2);
    cr_assert_stderr_eq_str("No $home variable set.\n");
    cr_assert_eq(ret, 1);
    cr_assert_eq(ret2, 0);
}

Test(builtin, cd_prev, .init=cr_redirect_stderr)
{
    environment_t *env = NULL;
    environment_t *pwd = NULL;
    environment_t *oldpwd = NULL;
    char *args[3] = {"cd", "/etc", NULL};
    char *args2[3] = {"cd", "-", NULL};
    shell_t shell = {0, 0};
    shell_t shell2 = {0, 0};

    builtin_cd(&env, args);
    builtin_cd(&env, args2);
    silent_cd(&env, args, &shell);
    silent_cd(&env, args2, &shell2);
    cr_assert_eq(shell.ret, 0);
    cr_assert_eq(shell2.ret, 0);
    pwd = get_env_value(env, "PWD");
    oldpwd = get_env_value(env, "OLDPWD");
    cr_assert_not_null(pwd);
    cr_assert_not_null(oldpwd);
    cr_assert_str_eq(oldpwd->value, "/etc");
}

Test(builtin, cd_prev_usage, .init=cr_redirect_stderr)
{
    int ret = 0;
    environment_t *env = NULL;
    char *args[3] = {"cd", "-a", NULL};
    shell_t shell = {0, 0};

    builtin_cd(&env, args);
    ret = silent_cd(&env, args, &shell);
    cr_assert_stderr_eq_str("Usage: cd [-plvn][-|<dir>].\n");
    cr_assert_eq(ret, 1);
}

Test(builtin, cd_prev_unexisting, .init=cr_redirect_stderr)
{
    int ret = 0;
    environment_t *env = NULL;
    char *args[3] = {"cd", "-", NULL};
    shell_t shell = {0, 0};

    builtin_cd(&env, args);
    ret = silent_cd(&env, args, &shell);
    cr_assert_stderr_eq_str(": No such file or directory.\n");
    cr_assert_eq(ret, 1);
}

Test(builtin, cd_empty, .init=cr_redirect_stderr)
{
    int ret = 0;
    environment_t *env = NULL;
    environment_t *pwd = NULL;
    environment_t *oldpwd = NULL;
    char *args[3] = {"cd", "", NULL};
    shell_t shell = {0, 0};

    builtin_cd(&env, args);
    ret = silent_cd(&env, args, &shell);
    cr_assert_eq(ret, 1);
    pwd = get_env_value(env, "PWD");
    oldpwd = get_env_value(env, "OLDPWD");
    cr_assert_null(pwd);
    cr_assert_null(oldpwd);
    cr_assert_stderr_eq_str(": No such file or directory.\n");
}
