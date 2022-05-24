/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** History'
*/

#pragma once

#include "types.h"

// Interact
void add_history(const char *input, shell_t *shell);
void free_history(void *elem);
char *get_history_command(list_t *history, int index);

void replace_history(char **input, shell_t *shell);
