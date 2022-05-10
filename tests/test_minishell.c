/*
** EPITECH PROJECT, 2021
** minishell2
** File description:
** Unit tests
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <signal.h>
#include "builtin.h"
#include "minishell.h"
#include "my_string.h"
#include "varenv.h"

Test(input, empty)
{
    char *input = " \t\t  \n";
    varenv_t *env = NULL;
    minishell_t shell = { 0, 0 };

    handle_input(input, &env, &shell);
    cr_assert_eq(shell.ret, 0);
}

Test(input, command, .init=cr_redirect_stderr)
{
    char *input = "ls\n";
    varenv_t *env = malloc(sizeof(varenv_t));
    minishell_t shell = { 0, 0 };

    cr_redirect_stdout();
    env->key = "PATH";
    env->value = "/bin";
    handle_input(input, &env, &shell);
    cr_assert_stderr_neq_str("ls: Command not found.\n");
    cr_assert_eq(shell.ret, 0);
}

Test(input, builtin, .init=cr_redirect_stdout)
{
    char *input = "env\n";
    varenv_t *env = malloc(sizeof(varenv_t));
    minishell_t shell = { 0, 0 };

    env->key = "PATH";
    env->value = "/bin";
    handle_input(input, &env, &shell);
    cr_assert_stdout_eq_str("PATH=/bin\n");
    cr_assert_eq(shell.ret, 0);
}

Test(input, folder, .init=cr_redirect_stderr)
{
    char *input = "/etc\n";
    varenv_t *env = NULL;
    minishell_t shell = { 0, 0 };

    handle_input(input, &env, &shell);
    cr_assert_stderr_eq_str("/etc: Permission denied.\n");
}

Test(input, no_path, .init=cr_redirect_stderr)
{
    char *input = "ls\n";
    varenv_t *env = malloc(sizeof(varenv_t));
    minishell_t shell = { 0, 0 };

    env->key = "PATH";
    env->value = "/";
    handle_input(input, &env, &shell);
    cr_assert_stderr_eq_str("ls: Command not found.\n");
}

Test(input, not_found, .init=cr_redirect_stderr)
{
    char *input = "lsa\n";
    varenv_t *env = NULL;
    minishell_t shell = { 0, 0 };

    handle_input(input, &env, &shell);
    cr_assert_stderr_eq_str("lsa: Command not found.\n");
}

Test(error, no_env)
{
    varenv_t **env = NULL;
    minishell_t shell = { 1, 0 };

    shell_heartbeat(env, &shell);
    cr_assert_eq(shell.ret, 0);
}

Test(error, shell_exit, .init=cr_redirect_stderr)
{
    int out = minishell(NULL);

    cr_assert_stderr_eq_str("Error: Invalid environment.\n");
    cr_assert_eq(out, 84);
}

Test(error, segmentation_fault, .init=cr_redirect_stderr)
{
    char *input = "./tests/samples/segfault_coredumped\n";
    varenv_t *env = malloc(sizeof(varenv_t));
    minishell_t shell = { 0, 0 };

    env->key = "PATH";
    env->value = "/bin";
    handle_input(input, &env, &shell);
    cr_assert_stderr_eq_str("Segmentation fault (core dumped)\n");
}

Test(error, floating_exception, .init=cr_redirect_stderr)
{
    char *input = "./tests/samples/div_zero\n";
    varenv_t *env = malloc(sizeof(varenv_t));
    minishell_t shell = { 0, 0 };

    env->key = "PATH";
    env->value = "/bin";
    handle_input(input, &env, &shell);
    cr_assert_stderr_eq_str("Floating exception (core dumped)\n");
}

Test(error, corrupted, .init=cr_redirect_stderr)
{
    char *input = "./tests/samples/corrupted\n";
    varenv_t *env = malloc(sizeof(varenv_t));
    minishell_t shell = { 0, 0 };

    env->key = "PATH";
    env->value = "/bin";
    handle_input(input, &env, &shell);
    cr_assert_stderr_eq_str("./tests/samples/corrupted: Exec format error. Wrong Architecture.\n");
}

Test(signal, sigquit, .init=cr_redirect_stdout)
{
    handle_quit(SIGINT);
    cr_assert_stdout_eq_str("\n$> ");
}

Test(varenv, convert)
{
    char **env = malloc(sizeof(char *) * 3);
    varenv_t *list = convert_env(env);

    env[0] = "PATH=/bin";
    env[1] = "HOME=/home";
    env[2] = NULL;
    list = convert_env(env);
    cr_assert_str_eq(list->key, "PATH");
    cr_assert_str_eq(list->value, "/bin");
    cr_assert_not_null(list->next);
    cr_assert_str_eq(list->next->key, "HOME");
    cr_assert_str_eq(list->next->value, "/home");
    cr_assert_null(list->next->next);
    destroy_env(list);
}

Test(varenv, error_handling)
{
    char *str = "salut";
    char *key = extract_key(str);
    char *value = extract_value(str);

    cr_assert_null(key);
    cr_assert_null(value);
}

Test(varenv, remove_first)
{
    varenv_t *env = malloc(sizeof(varenv_t));
    varenv_t *path = malloc(sizeof(varenv_t));

    env->key = my_strdup("HOME");
    env->value = my_strdup("/home");
    env->next = path;
    path->key = "PATH";
    path->value = "/path";
    varenv_remove(&env, "HOME");
    cr_assert_str_eq(env->key, "PATH");
}

Test(directories, unexisting_file)
{
    int out = check_directory("./bonsoir");

    cr_assert_eq(out, false);
}
