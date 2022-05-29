/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Unit tests on builtins
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "builtin.h"

Test(builtin, command_check)
{
    bool valid = is_builtin("cd");
    bool invalid = is_builtin("ls");

    cr_assert_eq(valid, true);
    cr_assert_eq(invalid, false);
}
