/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Unit tests for builtin environment
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "environment.h"
#include "builtin.h"

Test(env, list, .init=cr_redirect_stdout)
{
    env_t path = {"PATH", "/usr/bin:/bin", NULL};
    char *const args[2] = {"env", NULL};
    shell_t shell = {0, 0, &path, NULL, NULL, NULL};

    setbuf(stdout, NULL);
    builtin_env(&shell, args);
    cr_assert_stdout_eq_str("PATH=/usr/bin:/bin\n");
    cr_assert_eq(shell.ret, 0);
}

Test(setenv, simple)
{
    env_t path = {"PATH", strdup("/usr/bin:/bin"), NULL};
    char *const args[4] = {"setenv", "PATH", "/etc", NULL};
    shell_t shell = {0, 0, &path, NULL, NULL, NULL};

    silent_setenv(&shell, args);
    cr_assert_str_eq(path.value, "/etc");
    cr_assert_eq(shell.ret, 0);
    free(path.value);
}

Test(setenv, print, .init=cr_redirect_stdout)
{
    env_t path = {"PATH", strdup("/usr/bin:/bin"), NULL};
    char *const args[2] = {"setenv", NULL};
    shell_t shell = {0, 0, &path, NULL, NULL, NULL};

    setbuf(stdout, NULL);
    builtin_setenv(&shell, args);
    silent_setenv(&shell, args);
    cr_assert_str_eq(path.value, "/usr/bin:/bin");
    cr_assert_eq(shell.ret, 0);
    cr_assert_stdout_eq_str("PATH=/usr/bin:/bin\n");
    free(path.value);
}

Test(setenv, alphanumeric, .init=cr_redirect_stderr)
{
    env_t *env = NULL;
    char *const args[3] = {"setenv", "PATH=", NULL};
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    builtin_setenv(&shell, args);
    silent_setenv(&shell, args);
    cr_assert_null(env);
    cr_assert_stderr_eq_str("setenv: Variable name must contain alphanumeric characters.\n");
}

Test(setenv, begin_letter, .init=cr_redirect_stderr)
{
    env_t *env = NULL;
    char *const args[3] = {"setenv", "42b", NULL};
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    builtin_setenv(&shell, args);
    silent_setenv(&shell, args);
    cr_assert_null(env);
    cr_assert_stderr_eq_str("setenv: Variable name must begin with a letter.\n");
}

Test(setenv, too_many_args, .init=cr_redirect_stderr)
{
    char *const args[5] = {"setenv", "PATH", "key", "value", NULL};
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    builtin_setenv(&shell, args);
    cr_assert_eq(silent_setenv(&shell, args), 1);
    cr_assert_null(shell.env);
    cr_assert_stderr_eq_str("setenv: Too many arguments.\n");
}

Test(unsetenv, basic)
{
    env_t *env = malloc(sizeof(env_t));
    env_t *path = malloc(sizeof(env_t));
    char *args[3] = {"unsetenv", "PATH", NULL};
    shell_t shell = {0, 0, env, NULL, NULL, NULL};

    shell.env->key = strdup("HOME");
    shell.env->value = strdup("/home");
    shell.env->next = path;
    path->key = strdup("PATH");
    path->value = strdup("/usr");
    path->next = NULL;
    builtin_unsetenv(&shell, args);
    cr_assert_eq(silent_unsetenv(&shell, args), 0);
    cr_assert_null(shell.env->next);
    destroy_env(env);
}

Test(unsetenv, no_args, .init=cr_redirect_stderr)
{
    char *const args[2] = {"unsetenv", NULL};
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    builtin_unsetenv(&shell, args);
    cr_assert_eq(silent_unsetenv(&shell, args), 1);
    cr_assert_stderr_eq_str("unsetenv: Too few arguments.\n");
}

Test(unsetenv, all)
{
    env_t *env = malloc(sizeof(env_t));
    env_t *path = malloc(sizeof(env_t));
    char *const args[3] = {"unsetenv", "*", NULL};
    shell_t shell = {0, 0, env, NULL, NULL, NULL};

    shell.env->key = strdup("HOME");
    shell.env->value = strdup("/home");
    shell.env->next = path;
    path->key = strdup("PATH");
    path->value = strdup("/usr");
    path->next = NULL;
    builtin_unsetenv(&shell, args);
    silent_unsetenv(&shell, args);
    cr_assert_null(shell.env);
    cr_assert_eq(shell.ret, 0);
}

Test(unsetenv, all_error, .init=cr_redirect_stderr)
{
    env_t *env = malloc(sizeof(env_t));
    env_t *path = malloc(sizeof(env_t));
    char *const args[4] = {"unsetenv", "*", "bonsoir", NULL};
    shell_t shell = {0, 0, env, NULL, NULL, NULL};

    env->key = strdup("HOME");
    env->value = strdup("/home");
    env->next = path;
    path->key = strdup("PATH");
    path->value = strdup("/usr");
    path->next = NULL;
    builtin_unsetenv(&shell, args);
    silent_unsetenv(&shell, args);
    cr_assert_not_null(shell.env);
    cr_assert_eq(shell.ret, 0);
    destroy_env(env);
}
