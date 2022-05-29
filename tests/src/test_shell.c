/*
** EPITECH PROJECT, 2022
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
    shell_t shell = {0, 0, false, NULL, NULL, NULL, NULL};

    handle_input(input, &shell);
    cr_assert_eq(shell.ret, 0);
}

Test(input, command, .init=cr_redirect_stderr)
{
    const char *input = "ls\n";
    env_t *env = malloc(sizeof(env_t));
    shell_t shell = {0, 0, false, env, NULL, NULL, NULL};

    cr_redirect_stdout();
    env->key = "PATH";
    env->value = "/bin";
    handle_input(input, &shell);
    cr_assert_stderr_neq_str("ls: Command not found.\n");
    cr_assert_eq(shell.ret, 0);
}

Test(input, builtin, .init=cr_redirect_stdout)
{
    const char *input = "env\n";
    env_t *env = malloc(sizeof(env_t));
    shell_t shell = {0, 0, false, env, NULL, NULL, NULL};

    env->key = "PATH";
    env->value = "/bin";
    handle_input(input, &shell);
    cr_assert_stdout_eq_str("PATH=/bin\n");
    cr_assert_eq(shell.ret, 0);
}

Test(input, folder, .init=cr_redirect_stderr)
{
    const char *input = "/etc\n";
    shell_t shell = {0, 0, false, NULL, NULL, NULL, NULL};

    handle_input(input, &shell);
    cr_assert_stderr_eq_str("/etc: Permission denied.\n");
}

Test(input, no_path, .init=cr_redirect_stderr)
{
    const char *input = "ls\n";
    env_t *env = malloc(sizeof(env_t));
    shell_t shell = {0, 0, false, NULL, NULL, NULL, NULL};

    env->key = "PATH";
    env->value = "/";
    handle_input(input, &shell);
    cr_assert_stderr_eq_str("ls: Command not found.\n");
}

Test(input, not_found, .init=cr_redirect_stderr)
{
    const char *input = "lsa\n";
    shell_t shell = {0, 0, false, NULL, NULL, NULL, NULL};

    handle_input(input, &shell);
    cr_assert_stderr_eq_str("lsa: Command not found.\n");
}

Test(error, no_env)
{
    shell_t shell = {1, 0, false, NULL, NULL, NULL, NULL};

    do_heartbeat(&shell, NULL);
    cr_assert_eq(shell.ret, 0);
}

Test(error, shell_exit, .init=cr_redirect_stderr)
{
    cr_assert_eq(start_shell(NULL), 84);
    cr_assert_stderr_eq_str("Error: Invalid environment.\n");
}

Test(error, segmentation_fault, .init=cr_redirect_stderr)
{
    const char *input = "./tests/samples/segfault_coredumped\n";
    env_t *env = malloc(sizeof(env_t));
    shell_t shell = {0, 0, false, NULL, NULL, NULL, NULL};

    env->key = "PATH";
    env->value = "/bin";
    handle_input(input, &shell);
    cr_assert_stderr_eq_str("Segmentation fault (core dumped)\n");
}

Test(error, floating_exception, .init=cr_redirect_stderr)
{
    const char *input = "./tests/samples/div_zero\n";
    env_t *env = malloc(sizeof(env_t));
    shell_t shell = {0, 0, false, NULL, NULL, NULL, NULL};

    env->key = "PATH";
    env->value = "/bin";
    handle_input(input, &shell);
    cr_assert_stderr_eq_str("Floating exception (core dumped)\n");
}

Test(error, corrupted, .init=cr_redirect_stderr)
{
    const char *input = "./tests/samples/corrupted\n";
    env_t *env = malloc(sizeof(env_t));
    shell_t shell = {0, 0, false, NULL, NULL, NULL, NULL};

    env->key = "PATH";
    env->value = "/bin";
    handle_input(input, &shell);
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
    const char *str = "salut";
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

Test(variables, home_tilde_not_set, .init=cr_redirect_stderr)
{
    const char *input = "ls ~ ; echo something\n";
    shell_t shell = {0, 0, false, NULL, NULL, NULL, NULL};

    handle_input(input, &shell);
    cr_assert_stderr_eq_str("No $home variable set.\necho: Command not found.\n");
}

Test(variables, other_not_set, .init=cr_redirect_stderr)
{
    const char *input = "echo $myvar ; echo something\n";
    shell_t shell = {0, 0, false, NULL, NULL, NULL, NULL};

    handle_input(input, &shell);
    cr_assert_stderr_eq_str("myvar: Undefined variable.\n");
}

Test(variables, other_set_local, .init=cr_redirect_stdout)
{
    const char *input = "echo $myvar ; echo something\n";
    env_t *env = malloc(sizeof(env_t));
    shell_t shell = {0, 0, false, env, NULL, NULL, NULL};

    env->key = "PATH";
    env->value = "/bin";
    env->next = NULL;
    add_localvar(&shell.localenv, "myvar", "content", false);
    handle_input(input, &shell);
    cr_assert_stdout_eq_str("content\nsomething\n");
    destroy_localenv(shell.localenv);
    free(env);
}

Test(variables, other_set_env, .init=cr_redirect_stdout)
{
    const char *input = "echo $myvar ; echo something\n";
    env_t *env = malloc(sizeof(env_t));
    shell_t shell = {0, 0, false, env, NULL, NULL, NULL};

    env->key = "PATH";
    env->value = "/bin";
    env->next = NULL;
    add_variable(&shell.env, "myvar", "content");
    handle_input(input, &shell);
    cr_assert_stdout_eq_str("content\nsomething\n");
    destroy_localenv(shell.localenv);
    free(env);
}

Test(variables, other_set_both, .init=cr_redirect_stdout)
{
    const char *input = "echo $myvar ; echo something\n";
    env_t *env = malloc(sizeof(env_t));
    shell_t shell = {0, 0, false, env, NULL, NULL, NULL};

    env->key = "PATH";
    env->value = "/bin";
    env->next = NULL;
    add_variable(&shell.env, "myvar", "content env");
    add_localvar(&shell.localenv, "myvar", "content local", false);
    handle_input(input, &shell);
    cr_assert_stdout_eq_str("content local\nsomething\n");
    destroy_localenv(shell.localenv);
    free(env);
}
