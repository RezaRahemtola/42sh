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
