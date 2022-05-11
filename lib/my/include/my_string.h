/*
** EPITECH PROJECT, 2022
** libmy
** File description:
** String module header
*/

#pragma once

#include <stdbool.h>

bool my_str_contains(char const *str, char const *pattern);
bool my_str_containschar(char const *str, char c);
bool my_str_starts(char const *str, char const *pattern);

bool my_char_isalpha(char c);

char **my_strsplit_many(char const *str, char const *list);

char *my_revstr(char const *str);
char *my_strrep(char *, char const *, char const *);
char **my_strsplit(char const *, char);
char *my_substr(char const *, int, int);
char *my_substr_size(char const *, int, int, int);
