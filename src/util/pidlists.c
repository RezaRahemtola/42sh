/*
** EPITECH PROJECT, 2022
** minishell2
** File description:
** Command linked lists
*/

#include <stdlib.h>
#include "types.h"

pidlist_t *create_pidlist(pid_t pid)
{
    pidlist_t *node = malloc(sizeof(pidlist_t));

    if (node == NULL) {
        return (NULL);
    }
    node->pid = pid;
    node->next = NULL;
    return (node);
}

void pidlist_append(pidlist_t **list, pidlist_t *node)
{
    pidlist_t *current = *list;

    if (*list == NULL) {
        *list = node;
        return;
    }
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = node;
}

void pidlist_free(pidlist_t *list)
{
    pidlist_t *current = list;
    pidlist_t *tmp = NULL;

    while (current != NULL) {
        tmp = current->next;
        free(current);
        current = tmp;
    }
}

int pidlist_size(pidlist_t *list)
{
    pidlist_t *current = list;
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
