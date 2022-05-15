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

bool check_and(command_t *cmd, char *const *array, const env_t *env);
bool check_or(command_t *cmd, char *const *array, const env_t *env);
bool check_semicolon(command_t *cmd, char *const *array, const env_t *env);

static const logical_t LOGICAL[4] = {
        { ";", &check_semicolon, SEMICOLON },
        { "&&", &check_and, AND },
        { "||", &check_or, OR},
        {0, 0, 0}
};
