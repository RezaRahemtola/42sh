/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Logical operators
*/

#pragma once

#include "types.h"

logical_t get_logical(const char *str, size_t index);
char **split_logical(const char *input);
void apply_logical(command_t *command, char const *separator);

bool check_logicals(command_t *list, shell_t *shell);
bool should_ignore(command_t *command);
size_t ignore_command(command_t *command);

static const logical_t LOGICAL[4] = {
        { ";", SEMICOLON },
        { "&&", AND },
        { "||", OR},
        {0, 0}
};
