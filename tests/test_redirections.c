/*
** EPITECH PROJECT, 2022
** minishell2
** File description:
** Unit tests on redirections
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <fcntl.h>
#include "minishell.h"

Test(redirections, valid_redirection, .init=cr_redirect_stdout)
{
    int fd = 0;
    const char *input = "ls > a\n";
    varenv_t *env = malloc(sizeof(varenv_t));
    minishell_t shell = { 0, 0 };

    env->key = "PATH";
    env->value = "/bin";
    handle_input(input, &env, &shell);
    fd = open("./a", O_RDONLY);
    remove("./a");
    cr_assert_eq(shell.ret, 0);
    cr_assert_neq(fd, -1);
}

Test(redirections, argument_after_redirection, .init=cr_redirect_stderr)
{
    int fd = 0;
    const char *input = "ls >> b -l\n";
    varenv_t *env = malloc(sizeof(varenv_t));
    minishell_t shell = { 0, 0 };

    env->key = "PATH";
    env->value = "/bin";
    handle_input(input, &env, &shell);
    fd = open("./b", O_RDONLY);
    remove("./b");
    cr_assert_neq(fd, -1);
}

Test(redirections, command_after_redirection, .init=cr_redirect_stdout)
{
    int fd = 0;
    const char *input = ">c ls\n";
    varenv_t *env = malloc(sizeof(varenv_t));
    minishell_t shell = { 0, 0 };

    env->key = "PATH";
    env->value = "/bin";
    handle_input(input, &env, &shell);
    fd = open("./c", O_RDONLY);
    remove("./c");
    cr_assert_eq(shell.ret, 0);
    cr_assert_neq(fd, -1);
}

Test(redirections, redirection_without_command, .init=cr_redirect_stderr)
{
    const char *input = "> a\n";
    varenv_t *env = NULL;
    minishell_t shell = { 0, 0 };

    handle_input(input, &env, &shell);
    cr_assert_stderr_eq_str("Invalid null command.\n");
    cr_assert_eq(shell.ret, 1);
}

Test(redirections, command_without_redirection, .init=cr_redirect_stderr)
{
    const char *input = "ls >\n";
    varenv_t *env = NULL;
    minishell_t shell = { 0, 0 };

    handle_input(input, &env, &shell);
    cr_assert_stderr_eq_str("Missing name for redirect.\n");
    cr_assert_eq(shell.ret, 1);
}

Test(redirections, unexisting_file, .init=cr_redirect_stderr)
{
    const char *input = "cat < a\n";
    varenv_t *env = malloc(sizeof(varenv_t));
    minishell_t shell = { 0, 0 };

    cr_redirect_stdout();
    env->key = "PATH";
    env->value = "/bin";
    handle_input(input, &env, &shell);
}

Test(redirections, valid_pipe, .init=cr_redirect_stdout)
{
    const char *input = "cat src/main.c | grep Main\n";
    varenv_t *env = malloc(sizeof(varenv_t));
    minishell_t shell = { 0, 0 };

    env->key = "PATH";
    env->value = "/bin";
    handle_input(input, &env, &shell);
    cr_assert_eq(shell.ret, 0);
    cr_assert_stdout_eq_str("** Main\n");
}

Test(redirections, invalid_pipe_left, .init=cr_redirect_stderr)
{
    const char *input = "   \t  | cat\n";
    varenv_t *env = malloc(sizeof(varenv_t));
    minishell_t shell = { 0, 0 };

    env->key = "PATH";
    env->value = "/bin";
    handle_input(input, &env, &shell);
    cr_assert_eq(shell.ret, 1);
    cr_assert_stderr_eq_str("Invalid null command.\n");
}

Test(redirections, invalid_pipe_start, .init=cr_redirect_stderr)
{
    const char *input = "| cat\n";
    varenv_t *env = malloc(sizeof(varenv_t));
    minishell_t shell = { 0, 0 };

    env->key = "PATH";
    env->value = "/bin";
    handle_input(input, &env, &shell);
    cr_assert_eq(shell.ret, 1);
    cr_assert_stderr_eq_str("Invalid null command.\n");
}

Test(redirections, invalid_pipe_right, .init=cr_redirect_stderr)
{
    const char *input = "cat src/main.c | \t\n";
    varenv_t *env = malloc(sizeof(varenv_t));
    minishell_t shell = { 0, 0 };

    env->key = "PATH";
    env->value = "/bin";
    handle_input(input, &env, &shell);
    cr_assert_eq(shell.ret, 1);
    cr_assert_stderr_eq_str("Invalid null command.\n");
}

Test(redirections, invalid_pipe_end, .init=cr_redirect_stderr)
{
    const char *input = "cat src/main.c |\n";
    varenv_t *env = malloc(sizeof(varenv_t));
    minishell_t shell = { 0, 0 };

    env->key = "PATH";
    env->value = "/bin";
    handle_input(input, &env, &shell);
    cr_assert_eq(shell.ret, 1);
    cr_assert_stderr_eq_str("Invalid null command.\n");
}

Test(redirections, double_input, .init=cr_redirect_stderr)
{
    const char *input = "cat src/main.c | cat < a\n";
    varenv_t *env = malloc(sizeof(varenv_t));
    minishell_t shell = { 0, 0 };

    env->key = "PATH";
    env->value = "/bin";
    handle_input(input, &env, &shell);
    cr_assert_eq(shell.ret, 1);
    cr_assert_stderr_eq_str("Ambiguous input redirect.\n");
}

Test(redirections, double_output, .init=cr_redirect_stderr)
{
    const char *input = "cat src/main.c >> a | cat\n";
    varenv_t *env = malloc(sizeof(varenv_t));
    minishell_t shell = { 0, 0 };

    env->key = "PATH";
    env->value = "/bin";
    handle_input(input, &env, &shell);
    cr_assert_eq(shell.ret, 1);
    cr_assert_stderr_eq_str("Ambiguous output redirect.\n");
}

Test(redirections, missing_name_input, .init=cr_redirect_stderr)
{
    const char *input = "cat src/main.c < \t  \n";
    varenv_t *env = malloc(sizeof(varenv_t));
    minishell_t shell = { 0, 0 };

    env->key = "PATH";
    env->value = "/bin";
    handle_input(input, &env, &shell);
    cr_assert_eq(shell.ret, 1);
    cr_assert_stderr_eq_str("Missing name for redirect.\n");
}

Test(redirections, missing_name_input_end, .init=cr_redirect_stderr)
{
    const char *input = "cat src/main.c <<\n";
    varenv_t *env = malloc(sizeof(varenv_t));
    minishell_t shell = { 0, 0 };

    env->key = "PATH";
    env->value = "/bin";
    handle_input(input, &env, &shell);
    cr_assert_eq(shell.ret, 1);
    cr_assert_stderr_eq_str("Missing name for redirect.\n");
}
