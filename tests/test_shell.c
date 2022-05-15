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
    env_t *env = NULL;
    shell_t shell = {0, 0};

    handle_input(input, &env, &shell);
    cr_assert_eq(shell.ret, 0);
}

Test(input, command, .init=cr_redirect_stderr)
{
    const char *input = "ls\n";
    env_t *env = malloc(sizeof(env_t));
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
    env_t *env = malloc(sizeof(env_t));
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
    env_t *env = NULL;
    shell_t shell = {0, 0};

    handle_input(input, &env, &shell);
    cr_assert_stderr_eq_str("/etc: Permission denied.\n");
}

Test(input, semicolon, .init=cr_redirect_stdout)
{
    const char *input = "echo test1 ; echo test2 ; echo test3\n";
    env_t *env = malloc(sizeof(env_t));
    shell_t shell = {0, 0};

    env->key = "PATH";
    env->value = "/bin";
    handle_input(input, &env, &shell);
    cr_assert_stdout_eq_str("test1\ntest2\ntest3\n");
}

Test(input, no_path, .init=cr_redirect_stderr)
{
    const char *input = "ls\n";
    env_t *env = malloc(sizeof(env_t));
    shell_t shell = {0, 0};

    env->key = "PATH";
    env->value = "/";
    handle_input(input, &env, &shell);
    cr_assert_stderr_eq_str("ls: Command not found.\n");
}

Test(input, not_found, .init=cr_redirect_stderr)
{
    const char *input = "lsa\n";
    env_t *env = NULL;
    shell_t shell = {0, 0};

    handle_input(input, &env, &shell);
    cr_assert_stderr_eq_str("lsa: Command not found.\n");
}

Test(input, and, .init=cr_redirect_stderr)
{
    const char *input = "echo salut && echo bonsoir\n";
    env_t *env = NULL;
    shell_t shell = {0, 0};

    handle_input(input, &env, &shell);
    cr_assert_stderr_eq_str("echo: Command not found.\n");
}

Test(input, or, .init=cr_redirect_stderr)
{
    const char *input = "echo salut && echo bonsoir\n";
    env_t *env = NULL;
    shell_t shell = {0, 0};

    handle_input(input, &env, &shell);
    cr_assert_stderr_eq_str("echo: Command not found.\necho: Command not found.\n");
}

Test(error, no_env)
{
    env_t **env = NULL;
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
    env_t *env = malloc(sizeof(env_t));
    shell_t shell = {0, 0};

    env->key = "PATH";
    env->value = "/bin";
    handle_input(input, &env, &shell);
    cr_assert_stderr_eq_str("Segmentation fault (core dumped)\n");
}

Test(error, floating_exception, .init=cr_redirect_stderr)
{
    const char *input = "./tests/samples/div_zero\n";
    env_t *env = malloc(sizeof(env_t));
    shell_t shell = {0, 0};

    env->key = "PATH";
    env->value = "/bin";
    handle_input(input, &env, &shell);
    cr_assert_stderr_eq_str("Floating exception (core dumped)\n");
}

Test(error, corrupted, .init=cr_redirect_stderr)
{
    const char *input = "./tests/samples/corrupted\n";
    env_t *env = malloc(sizeof(env_t));
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
    const char *const env[3] = {"PATH=/bin", "HOME=/home", NULL};
    env_t *list = get_env_from_array(env);

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
    env_t *env = malloc(sizeof(env_t));
    env_t *path = malloc(sizeof(env_t));

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
