/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Status handling
*/

#include "status.h"

bool must_relay_status(command_t *command)
{
    if (!command->prev)
        return false;
    if (command->prev->separator_next == SEMICOLON)
        return false;
    if (command->prev->separator_next == OR)
        return false;
    if (command->prev->ret == 0)
        return false;
    return true;
}
