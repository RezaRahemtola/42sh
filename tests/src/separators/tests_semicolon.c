/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Unit tests for ; separator
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "shell.h"

Test(semicolon, simple, .init=cr_redirect_stdout)
{
    const char *input = "echo test1 ; echo test2 ; echo test3\n";
    env_t *env = malloc(sizeof(env_t));
    shell_t shell = {0, 0, env, NULL, NULL, NULL};

    env->key = "PATH";
    env->value = "/bin";
    handle_input(input, &shell);
    cr_assert_stdout_eq_str("test1\ntest2\ntest3\n");
    free(env);
}
