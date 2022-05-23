/*
** EPITECH PROJECT, 2022
** libmy
** File description:
** Linked list module header
*/

#pragma once

#include <stdbool.h>

typedef struct list_s {
    void *data;
    struct list_s *prev;
    struct list_s *next;
} list_t;

typedef bool (*equals_func)(void *obj1, void *obj2);
typedef void (*free_func)(void *obj);

void my_list_add(list_t **list, void *data);
void my_list_add_index(list_t **list, void *data, size_t index);
void my_list_remove(list_t **list, void *data, equals_func eq_func, \
free_func free_func);
void my_list_remove_all(list_t **list, void *data, equals_func eq_func, \
free_func free_func);
void my_list_remove_index(list_t **list, size_t index, free_func free_func);

size_t my_list_size(list_t *list);
bool my_list_contains(list_t *list, void *data, equals_func eq_func);
void my_list_free(list_t *list, free_func free_func);
