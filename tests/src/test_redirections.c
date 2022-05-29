/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Unit tests on redirections
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <fcntl.h>
#include <unistd.h>
#include "shell.h"

Test(redirections, valid_redirection)
{
    int fd = 0;
    const char *input = "ls > a\n";
    env_t *env = malloc(sizeof(env_t));
    shell_t shell = {0, 0, env, NULL, NULL, NULL};

    env->key = "PATH";
    env->value = "/bin";
    handle_input(input, &shell);
    fd = open("./a", O_RDONLY);
    remove("./a");
    cr_assert_eq(shell.ret, 0);
    cr_assert_neq(fd, -1);
    free(env);
    close(fd);
}

Test(redirections, argument_after_redirection, .init=cr_redirect_stderr)
{
    int fd = 0;
    const char *input = "ls >> b -l\n";
    env_t *env = malloc(sizeof(env_t));
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    env->key = "PATH";
    env->value = "/bin";
    handle_input(input, &shell);
    fd = open("./b", O_RDONLY);
    remove("./b");
    cr_assert_neq(fd, -1);
    free(env);
    close(fd);
}

Test(redirections, command_after_redirection)
{
    int fd = 0;
    const char *input = ">c ls\n";
    env_t *env = malloc(sizeof(env_t));
    shell_t shell = {0, 0, env, NULL, NULL, NULL};

    env->key = "PATH";
    env->value = "/bin";
    handle_input(input, &shell);
    fd = open("./c", O_RDONLY);
    remove("./c");
    cr_assert_eq(shell.ret, 0);
    cr_assert_neq(fd, -1);
    free(env);
    close(fd);
}

Test(redirections, redirection_without_command, .init=cr_redirect_stderr)
{
    const char *input = "> a\n";
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    handle_input(input, &shell);
    cr_assert_stderr_eq_str("Invalid null command.\n");
    cr_assert_eq(shell.ret, 1);
}

Test(redirections, command_without_redirection, .init=cr_redirect_stderr)
{
    const char *input = "ls >\n";
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    handle_input(input, &shell);
    cr_assert_stderr_eq_str("Missing name for redirect.\n");
    cr_assert_eq(shell.ret, 1);
}

Test(redirections, unexisting_file, .init=cr_redirect_stderr)
{
    const char *input = "cat < d\n";
    env_t *env = malloc(sizeof(env_t));
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    env->key = "PATH";
    env->value = "/bin";
    handle_input(input, &shell);
    cr_assert_stderr_eq_str("d: No such file or directory.\n");
    free(env);
}

Test(redirections, valid_pipe, .init=cr_redirect_stdout)
{
    const char *input = "cat src/main.c | grep Main\n";
    env_t *env = malloc(sizeof(env_t));
    shell_t shell = {0, 0, env, NULL, NULL, NULL};

    env->key = "PATH";
    env->value = "/bin";
    handle_input(input, &shell);
    cr_assert_eq(shell.ret, 0);
    cr_assert_stdout_eq_str("** Main\n");
    free(env);
}

Test(redirections, invalid_pipe_left, .init=cr_redirect_stderr)
{
    const char *input = "   \t  | cat\n";
    env_t *env = malloc(sizeof(env_t));
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    env->key = "PATH";
    env->value = "/bin";
    handle_input(input, &shell);
    cr_assert_eq(shell.ret, 1);
    cr_assert_stderr_eq_str("Invalid null command.\n");
    free(env);
}

Test(redirections, invalid_pipe_start, .init=cr_redirect_stderr)
{
    const char *input = "| cat\n";
    env_t *env = malloc(sizeof(env_t));
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    env->key = "PATH";
    env->value = "/bin";
    handle_input(input, &shell);
    cr_assert_eq(shell.ret, 1);
    cr_assert_stderr_eq_str("Invalid null command.\n");
    free(env);
}

Test(redirections, invalid_pipe_right, .init=cr_redirect_stderr)
{
    const char *input = "cat src/main.c | \t\n";
    env_t *env = malloc(sizeof(env_t));
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    env->key = "PATH";
    env->value = "/bin";
    handle_input(input, &shell);
    cr_assert_eq(shell.ret, 1);
    cr_assert_stderr_eq_str("Invalid null command.\n");
    free(env);
}

Test(redirections, invalid_pipe_end, .init=cr_redirect_stderr)
{
    const char *input = "cat src/main.c |\n";
    env_t *env = malloc(sizeof(env_t));
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    env->key = "PATH";
    env->value = "/bin";
    handle_input(input, &shell);
    cr_assert_eq(shell.ret, 1);
    cr_assert_stderr_eq_str("Invalid null command.\n");
    free(env);
}

Test(redirections, double_input, .init=cr_redirect_stderr)
{
    const char *input = "cat src/main.c | cat < a\n";
    env_t *env = malloc(sizeof(env_t));
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    env->key = "PATH";
    env->value = "/bin";
    handle_input(input, &shell);
    cr_assert_eq(shell.ret, 1);
    cr_assert_stderr_eq_str("Ambiguous input redirect.\n");
    free(env);
}

Test(redirections, double_output, .init=cr_redirect_stderr)
{
    const char *input = "cat src/main.c >> a | cat\n";
    env_t *env = malloc(sizeof(env_t));
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    env->key = "PATH";
    env->value = "/bin";
    handle_input(input, &shell);
    cr_assert_eq(shell.ret, 1);
    cr_assert_stderr_eq_str("Ambiguous output redirect.\n");
    free(env);
}

Test(redirections, missing_name_input, .init=cr_redirect_stderr)
{
    const char *input = "cat src/main.c < \t  \n";
    env_t *env = malloc(sizeof(env_t));
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    env->key = "PATH";
    env->value = "/bin";
    handle_input(input, &shell);
    cr_assert_eq(shell.ret, 1);
    cr_assert_stderr_eq_str("Missing name for redirect.\n");
    free(env);
}

Test(redirections, missing_name_input_end, .init=cr_redirect_stderr)
{
    const char *input = "cat src/main.c <<\n";
    env_t *env = malloc(sizeof(env_t));
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    env->key = "PATH";
    env->value = "/bin";
    handle_input(input, &shell);
    cr_assert_eq(shell.ret, 1);
    cr_assert_stderr_eq_str("Missing name for redirect.\n");
    free(env);
}
