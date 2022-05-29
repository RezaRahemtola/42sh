/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Unit tests for && separator
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "shell.h"

Test(and, command_not_found, .init=cr_redirect_stderr)
{
    const char *input = "echo salut && echo bonsoir\n";
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    handle_input(input, &shell);
    cr_assert_stderr_eq_str("echo: Command not found.\n");
}

Test(and, simple, .init=cr_redirect_stdout)
{
    const char *input = "echo foo && echo bar\n";
    env_t *env = malloc(sizeof(env_t));
    shell_t shell = {0, 0, env, NULL, NULL, NULL};

    env->key = "PATH";
    env->value = "/bin";
    handle_input(input, &shell);
    cr_assert_stdout_eq_str("foo\nbar\n");
    free(env);
}

Test(and, no_commands, .init=cr_redirect_stderr)
{
    const char *input = "&&\n";
    env_t *env = malloc(sizeof(env_t));
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    env->key = "PATH";
    env->value = "/bin";
    handle_input(input, &shell);
    cr_assert_stderr_neq_str("Invalid null command.\n");
    free(env);
}

Test(and, no_left, .init=cr_redirect_stdout)
{
    const char *input = "&& echo foo\n";
    env_t *env = malloc(sizeof(env_t));
    shell_t shell = {0, 0, env, NULL, NULL, NULL};

    env->key = "PATH";
    env->value = "/bin";
    handle_input(input, &shell);
    cr_assert_stdout_eq_str("foo\n");
    free(env);
}

Test(and, no_right, .init=cr_redirect_stderr)
{
    const char *input = "echo foo &&\n";
    env_t *env = malloc(sizeof(env_t));
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    env->key = "PATH";
    env->value = "/bin";
    handle_input(input, &shell);
    cr_assert_stderr_eq_str("Invalid null command.\n");
    free(env);
}
