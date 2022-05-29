/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Graphics header
*/

#pragma once

#include "types.h"

typedef struct line {
    char *str;
    int size;
    int length;
    int pos;
} line_t;

typedef void (*arrow_handler_t)(line_t *line, int *count, shell_t *shell);

static const int BUFFER_SIZE = 128;

void init_graphics(shell_t *shell);

ssize_t get_line_content(char **line, size_t *size, shell_t *shell);
char *get_user_input(shell_t *shell);
void handle_special_key(line_t *line, int *count, shell_t *shell);
void move_cursor(int delta, line_t *line);
void backspace(line_t *line);
char *get_prompt(void);
void print_line(line_t *line);
void set_line(line_t *line, char const *new_line);

void arrow_up(line_t *line, int *count, shell_t *shell);
void arrow_down(line_t *line, int *count, shell_t *shell);
void arrow_left(line_t *line, int *count, shell_t *shell);
void arrow_right(line_t *line, int *count, shell_t *shell);

static const arrow_handler_t ARROW_HANDLERS[4] = {
        &arrow_up,
        &arrow_down,
        &arrow_left,
        &arrow_right
};
