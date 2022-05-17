/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Functions to skip commands
*/

#include <stddef.h>
#include "redirections.h"
#include "skipping.h"

void skip_to_next_cmd(command_t **list, size_t *total)
{
    command_t *cmd = *list;

    if (cmd != NULL) {
        *total += 1;
        close_redirections(cmd);
        *list = cmd->next;
    }
}

static bool is_next_logical(command_t *cmd)
{
    if (cmd == NULL)
        return (false);
    if (cmd->separator_next != AND && cmd->separator_next != OR)
        return (false);
    return (true);
}

void skip_logicals(command_t **list, size_t *total)
{
    command_t *current = *list;

    while (is_next_logical(current))
        skip_to_next_cmd(&current, total);
    skip_to_next_cmd(&current, total);
    skip_to_next_cmd(&current, total);
}
