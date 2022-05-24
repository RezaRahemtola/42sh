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

static void move_start(list_t **list, list_t *node)
{
    if (*list != NULL) {
        list[0]->prev = node;
        node->next = *list;
    }
    *list = node;
}

static void move_in(list_t *current, list_t *node)
{
    list_t *tmp = current->next;

    current->next = node;
    node->prev = current;
    node->next = tmp;
    if (tmp != NULL)
        tmp->prev = node;
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

void my_list_add_index(list_t **list, void *data, size_t index)
{
    list_t *node = init_node(data);
    list_t *current = *list;
    size_t size = my_list_size(*list);

    if (node == NULL || index > size)
        return;
    if (index == size) {
        my_list_add(list, data);
        return;
    }
    if (index == 0) {
        move_start(list, node);
        return;
    }
    for (size_t i = 1; i < index; i++)
        current = current->next;
    move_in(current, node);
}
