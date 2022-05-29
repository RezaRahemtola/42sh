/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Line content functions
*/

#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include "graphics.h"

ssize_t get_line_content(char **line, size_t *size, shell_t *shell)
{
    struct termios old;
    struct termios new;

    if (!shell->graphical)
        return getline(line, size, stdin);
    tcgetattr(STDIN_FILENO, &old);
    new = old;
    new.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new);
    printf("$> ");
    *line = get_user_input();
    tcsetattr(STDIN_FILENO, TCSANOW, &old);
    if (*line == NULL)
        return -1;
    return ((ssize_t) strlen(*line));
}
