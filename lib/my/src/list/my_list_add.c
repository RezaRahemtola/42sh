/*
** EPITECH PROJECT, 2022
** libmy
** File description:
** List adding functions
*/

#include <stdlib.h>
#include "my_list.h"

static list_t *init_node(void *data)
{
    list_t *node = malloc(sizeof(list_t));

    if (node == NULL)
        return (NULL);
    node->data = data;
    node->prev = NULL;
    node->next = NULL;
    return (node);
}

void my_list_add(list_t **list, void *data)
{
    list_t *node = init_node(data);
    list_t *current = *list;

    if (node == NULL)
        return;
    if (*list == NULL) {
        *list = node;
        return;
    }
    while (current->next != NULL)
        current = current->next;
    current->next = node;
    node->prev = current;
}
