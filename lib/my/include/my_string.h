/*
** EPITECH PROJECT, 2022
** libmy
** File description:
** String module header
*/

#pragma once

#include <stdbool.h>

bool my_str_contains(const char *str, const char *pattern);
bool my_str_containschar(const char *str, char c);
bool my_str_starts(const char *str, const char *pattern);

bool my_char_isalpha(char c);

char **my_strsplit_many(const char *str, const char *list);

char *my_revstr(const char *str);
char *my_strrep(const char *str, const char *pattern, const char *new);
char **my_strsplit(const char *str, char separator);
char *my_substr(const char *str, int start, int end);
char *my_substr_size(const char *str, int start, int end, int size);
