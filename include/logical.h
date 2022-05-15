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

bool check_and(command_t *cmd, char *const *array, const env_t *env);
bool check_or(command_t *cmd, char *const *array, const env_t *env);
bool check_semicolon(command_t *cmd, char *const *array, const env_t *env);

static const logical_t LOGICAL[4] = {
        { "&&", &check_and },
        { "||", &check_or},
        { ";", &check_semicolon },
        {0, 0}
};
