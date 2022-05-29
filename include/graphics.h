/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Graphics header
*/

#pragma once

#include "types.h"

static const int BUFFER_SIZE = 128;

void init_graphics(shell_t *shell);
ssize_t get_line_content(char **line, size_t *size, shell_t *shell);
char *get_user_input(void);