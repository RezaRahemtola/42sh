/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Command linked lists
*/

#include <stdlib.h>
#include "types.h"
#include "my_arrays.h"

void list_append(command_t **list, command_t *node)
{
    command_t *current = *list;

    if (*list == NULL) {
        *list = node;
        return;
    }
    while (current->next != NULL)
        current = current->next;
    node->prev = current;
    current->next = node;
}

static void free_command(command_t *command)
{
    my_free_arrays(1, command->args);
    free(command->input);
    free(command->path);
    free(command->info_in);
    free(command->info_out);
    free(command);
}

void list_free(command_t *list)
{
    command_t *current = list;
    command_t *tmp = NULL;

    while (current != NULL) {
        tmp = current->next;
        free_command(current);
        current = tmp;
    }
}
