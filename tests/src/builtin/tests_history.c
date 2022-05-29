/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Unit tests for history builtin
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "builtin.h"
#include "history.h"
#include "my_string.h"

Test(history, simple, .init=cr_redirect_stdout)
{
    char *const args[2] = {"history", NULL};
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    add_history("ls -la", &shell);
    builtin_history(&shell, args);
    cr_assert_eq(silent_history(&shell, args), 0);
}

Test(history, not_a_number, .init=cr_redirect_stderr)
{
    char *const args[3] = {"history", "NaN", NULL};
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    builtin_history(&shell, args);
    cr_assert_eq(silent_history(&shell, args), 1);
    cr_assert_stderr_eq_str("history: Badly formed number.\n");
}

Test(history, badly_formed_number, .init=cr_redirect_stderr)
{
    char *const args[3] = {"history", "42NaN", NULL};
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    builtin_history(&shell, args);
    cr_assert_eq(silent_history(&shell, args), 1);
    cr_assert_stderr_eq_str("history: Badly formed number.\n");
}

Test(history, last_empty, .init=cr_redirect_stderr)
{
    char *input = strdup("!!\n");
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    replace_history(&input, &shell);
    cr_assert_stderr_eq_str("0: Event not found.\n");
    cr_assert_str_eq(input, " ");
    free(input);
}

Test(history, last, .init=cr_redirect_stdout)
{
    char *input = strdup("!!\n");
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    add_history("ls -la\n", &shell);
    replace_history(&input, &shell);
    cr_assert_str_eq(input, "ls -la\n");
    free(input);
}

Test(history, by_index_wrong, .init=cr_redirect_stderr)
{
    char *input = strdup("!3\n");
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    add_history("ls -la\n", &shell);
    replace_history(&input, &shell);
    cr_assert_stderr_eq_str("3: Event not found.\n");
    cr_assert_str_eq(input, " ");
    free(input);
}

Test(history, by_index, .init=cr_redirect_stdout)
{
    char *input = strdup("!1\n");
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    add_history("ls -la\n", &shell);
    replace_history(&input, &shell);
    cr_assert_str_eq(input, "ls -la\n");
    free(input);
}

Test(history, by_str_wrong, .init=cr_redirect_stderr)
{
    char *input = strdup("!cd\n");
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    add_history("ls -la\n", &shell);
    replace_history(&input, &shell);
    cr_assert_stderr_eq_str("cd: Event not found.\n");
    free(input);
}

Test(history, by_str, .init=cr_redirect_stdout)
{
    char *input = strdup("!ls\n");
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    add_history("ls -la\n", &shell);
    replace_history(&input, &shell);
    cr_assert_str_eq(input, "ls -la\n");
    free(input);
}

Test(history, by_backward_index_wrong, .init=cr_redirect_stderr)
{
    char *input = strdup("!-42\n");
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    replace_history(&input, &shell);
    cr_assert_stderr_eq_str("-42: Event not found.\n");
    free(input);
}

Test(history, by_backward_index, .init=cr_redirect_stdout)
{
    char *input = strdup("!-1\n");
    shell_t shell = {0, 0, NULL, NULL, NULL, NULL};

    add_history("ls -la\n", &shell);
    replace_history(&input, &shell);
    cr_assert_str_eq(input, "ls -la\n");
    free(input);
}
