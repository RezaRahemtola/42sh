/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Unit tests
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include <signal.h>
#include "builtin.h"
#include "shell.h"
#include "environment.h"

Test(input, empty)
{
    const char *input = " \t\t  \n";
    environment_t *env = NULL;
    shell_t shell = {0, 0};

    handle_input(input, &env, &shell);
    cr_assert_eq(shell.ret, 0);
}

Test(input, command, .init=cr_redirect_stderr)
{
    const char *input = "ls\n";
    environment_t *env = malloc(sizeof(environment_t));
    shell_t shell = {0, 0};

    cr_redirect_stdout();
    env->key = "PATH";
    env->value = "/bin";
    handle_input(input, &env, &shell);
    cr_assert_stderr_neq_str("ls: Command not found.\n");
    cr_assert_eq(shell.ret, 0);
}

Test(input, builtin, .init=cr_redirect_stdout)
{
    const char *input = "env\n";
    environment_t *env = malloc(sizeof(environment_t));
    shell_t shell = {0, 0};

    env->key = "PATH";
    env->value = "/bin";
    handle_input(input, &env, &shell);
    cr_assert_stdout_eq_str("PATH=/bin\n");
    cr_assert_eq(shell.ret, 0);
}

Test(input, folder, .init=cr_redirect_stderr)
{
    const char *input = "/etc\n";
    environment_t *env = NULL;
    shell_t shell = {0, 0};

    handle_input(input, &env, &shell);
    cr_assert_stderr_eq_str("/etc: Permission denied.\n");
}

Test(input, no_path, .init=cr_redirect_stderr)
{
    const char *input = "ls\n";
    environment_t *env = malloc(sizeof(environment_t));
    shell_t shell = {0, 0};

    env->key = "PATH";
    env->value = "/";
    handle_input(input, &env, &shell);
    cr_assert_stderr_eq_str("ls: Command not found.\n");
}

Test(input, not_found, .init=cr_redirect_stderr)
{
    const char *input = "lsa\n";
    environment_t *env = NULL;
    shell_t shell = {0, 0};

    handle_input(input, &env, &shell);
    cr_assert_stderr_eq_str("lsa: Command not found.\n");
}

Test(error, no_env)
{
    environment_t **env = NULL;
    shell_t shell = {1, 0};

    do_heartbeat(env, &shell);
    cr_assert_eq(shell.ret, 0);
}

Test(error, shell_exit, .init=cr_redirect_stderr)
{
    int out = start_shell(NULL);

    cr_assert_stderr_eq_str("Error: Invalid environment.\n");
    cr_assert_eq(out, 84);
}

Test(error, segmentation_fault, .init=cr_redirect_stderr)
{
    const char *input = "./tests/samples/segfault_coredumped\n";
    environment_t *env = malloc(sizeof(environment_t));
    shell_t shell = {0, 0};

    env->key = "PATH";
    env->value = "/bin";
    handle_input(input, &env, &shell);
    cr_assert_stderr_eq_str("Segmentation fault (core dumped)\n");
}

Test(error, floating_exception, .init=cr_redirect_stderr)
{
    const char *input = "./tests/samples/div_zero\n";
    environment_t *env = malloc(sizeof(environment_t));
    shell_t shell = {0, 0};

    env->key = "PATH";
    env->value = "/bin";
    handle_input(input, &env, &shell);
    cr_assert_stderr_eq_str("Floating exception (core dumped)\n");
}

Test(error, corrupted, .init=cr_redirect_stderr)
{
    const char *input = "./tests/samples/corrupted\n";
    environment_t *env = malloc(sizeof(environment_t));
    shell_t shell = {0, 0};

    env->key = "PATH";
    env->value = "/bin";
    handle_input(input, &env, &shell);
    cr_assert_stderr_eq_str("./tests/samples/corrupted: Exec format error. Wrong Architecture.\n");
}

Test(signal, sigquit, .init=cr_redirect_stdout)
{
    setbuf(stdout, NULL);
    handle_quit(SIGINT);
    cr_assert_stdout_eq_str("\n$> ");
}

Test(environment, convert)
{
    char **env = malloc(sizeof(char *) * 3);
    environment_t *list = get_env_from_array(env);

    env[0] = "PATH=/bin";
    env[1] = "HOME=/home";
    env[2] = NULL;
    list = get_env_from_array(env);
    cr_assert_str_eq(list->key, "PATH");
    cr_assert_str_eq(list->value, "/bin");
    cr_assert_not_null(list->next);
    cr_assert_str_eq(list->next->key, "HOME");
    cr_assert_str_eq(list->next->value, "/home");
    cr_assert_null(list->next->next);
    destroy_env(list);
}

Test(environment, error_handling)
{
    char *str = "salut";
    char *key = extract_env_key(str);
    char *value = extract_env_value(str);

    cr_assert_null(key);
    cr_assert_null(value);
}

Test(environment, remove_first)
{
    environment_t *env = malloc(sizeof(environment_t));
    environment_t *path = malloc(sizeof(environment_t));

    env->key = strdup("HOME");
    env->value = strdup("/home");
    env->next = path;
    path->key = "PATH";
    path->value = "/path";
    remove_env_property(&env, "HOME");
    cr_assert_str_eq(env->key, "PATH");
}

Test(directories, unexisting_file)
{
    cr_assert(!is_directory("./bonsoir"));
}
