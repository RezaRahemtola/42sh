/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Logical function checkers
*/

#include <stddef.h>
#include <stdio.h>
#include "logical.h"
#include "messages.h"
#include "shell.h"

static bool check_logical(const command_t *command, bool empty)
{
    command_t *prev = command->prev;
    bool prev_empty = (prev == NULL ? false : is_command_empty(prev));
    separator_next_type_t next = command->separator_next;

    if (empty && next == OR) {
        fprintf(stderr, "%s\n", MISSING_COMMAND);
        return (false);
    }
    if (empty && prev != NULL) {
        next = prev->separator_next;
        if (next == OR || (next == AND && !prev_empty)) {
            fprintf(stderr, "%s\n", MISSING_COMMAND);
            return (false);
        }
    }
    return (true);
}

bool check_logicals(command_t *list, shell_t *shell)
{
    bool empty = false;

    while (list != NULL) {
        empty = is_command_empty(list);
        if (!check_logical(list, empty)) {
            shell->ret = 1;
            return (false);
        }
        list = list->next;
    }
    return (true);
}

bool should_ignore(const command_t *command)
{
    if (command->prev == NULL)
        return (false);
    if (command->prev->separator_next == AND && command->prev->ret != 0)
        return (true);
    if (command->prev->separator_next == OR && command->prev->ret == 0)
        return (true);
    return (false);
}

size_t ignore_command(command_t *node)
{
    size_t total = 0;

    for (total = 0; node != NULL; total++) {
        if (node->next != NULL && node->next->separator_next == SEMICOLON)
            return (total + 2);
        node = node->next;
    }
    return (total);
}

void apply_logical(command_t *command, const char *separator)
{
    logical_t logical = get_logical(separator, 0);

    command->separator_next = logical.separator;
}
