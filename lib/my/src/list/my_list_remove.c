/*
** EPITECH PROJECT, 2022
** libmy
** File description:
** List removing functions
*/

#include <stdlib.h>
#include "my_list.h"

static void remove_data(list_t *node, list_t **list, free_func free_func)
{
    list_t *prev = node->prev;
    list_t *next = node->next;

    if (prev == NULL)
        *list = next;
    else
        prev->next = next;
    if (next != NULL)
        next->prev = prev;
    if (free_func != NULL)
        free_func(node->data);
    free(node);
}

void my_list_remove(list_t **list, void *data, equals_func eq_func, \
free_func free_func)
{
    list_t *current = *list;

    while (current != NULL) {
        if (eq_func(current->data, data)) {
            remove_data(current, list, free_func);
            return;
        }
        current = current->next;
    }
}

void my_list_remove_index(list_t **list, size_t index, free_func free_func)
{
    list_t *current = *list;
    size_t size = my_list_size(*list);

    if (index >= size)
        return;
    for (size_t i = 0; i < index - 1; i++)
        current = current->next;
    remove_data(current, list, free_func);
}

void my_list_remove_all(list_t **list, void *data, equals_func eq_func, \
free_func free_func)
{
    list_t *current = *list;
    list_t *tmp = NULL;
    bool equals = false;

    while (current != NULL) {
        equals = eq_func(current->data, data);
        if (equals) {
            tmp = current->next;
            remove_data(current, list, free_func);
            current = tmp;
        }
        if (!equals)
            current = current->next;
    }
}
