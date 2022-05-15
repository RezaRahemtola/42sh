/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Logical checks
*/

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "logical.h"
#include "messages.h"

static bool check_logical(command_t *command, bool empty)
{
    command_t *prev = command->prev;
    separatour_next_type_t next = command->separator_next;

    if (empty && next != NO_NEXT && next != SEMICOLON) {
        fprintf(stderr, "%s\n", MISSING_COMMAND);
        return (false);
    }
    if (empty && prev != NULL) {
        next = prev->separator_next;
        if (next != NO_NEXT && next != SEMICOLON) {
            fprintf(stderr, "%s\n", MISSING_COMMAND);
            return (false);
        }
    }
    return (true);
}

bool check_logicals(command_t *list, shell_t *shell)
{
    bool empty = false;
    command_t *current = list;

    while (current != NULL) {
        empty = (current->args[0] == NULL || strlen(current->args[0]) == 0);
        if (!check_logical(current, empty)) {
            shell->ret = 1;
            return (false);
        }
        current = current->next;
    }
    return (true);
}
