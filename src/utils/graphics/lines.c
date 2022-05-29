/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Line content functions
*/

#include <stdio.h>
#include "types.h"

ssize_t get_line_content(char **line, size_t *size, shell_t *shell)
{
    if (!shell->graphical) {
        return getline(line, size, stdin);
    } else {
        return getline(line, size, stdin);
    }
}
