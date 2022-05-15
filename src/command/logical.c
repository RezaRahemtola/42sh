/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Logical function checkers
*/

#include "logical.h"

bool check_and(command_t *cmd, char *const *array, const env_t *env)
{
    return (true);
}

bool check_or(command_t *cmd, char *const *array, const env_t *env)
{
    return (true);
}

bool check_semicolon(command_t *cmd, char *const *array, const env_t *env)
{
    return (true);
}

void apply_logical(command_t *command, char const *separator)
{
    logical_t logical = get_logical(separator, 0);

    command->separator_next = logical.separator;
}
