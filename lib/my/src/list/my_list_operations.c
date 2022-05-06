/*
** EPITECH PROJECT, 2022
** libmy
** File description:
** my_list_size function
*/

#include <stdlib.h>
#include "my_list.h"

int my_list_size(list_t *list)
{
    list_t *current = list;
    int size = 0;

    if (list == NULL) {
        return (0);
    }
    while (current != NULL) {
        size++;
        current = current->next;
    }
    return (size);
}

bool my_list_contains(list_t *list, void *data, equals_func eq_func)
{
    list_t *current = list;

    while (current != NULL) {
        if (eq_func(current->data, data) == true) {
            return (true);
        }
        current = current->next;
    }
    return (false);
}

void my_list_free(list_t *list, free_func free_func)
{
    list_t *current = list;
    list_t *tmp = NULL;

    while (current != NULL) {
        tmp = current->next;
        free_func(current->data);
        free(current);
        current = tmp;
    }
}
