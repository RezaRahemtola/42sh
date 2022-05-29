/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Command linked lists
*/

#include <stdlib.h>
#include "my_arrays.h"
#include "types.h"

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

size_t list_size(command_t *list)
{
    command_t *current = list;
    size_t size = 0;

    if (list == NULL)
        return (0);
    for (; current != NULL; size++)
        current = current->next;
    return (size);
}

void list_free(command_t *list)
{
    command_t *tmp = NULL;

    while (list != NULL) {
        tmp = list->next;
        free_command(list);
        list = tmp;
    }
}
