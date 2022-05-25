/*
** EPITECH PROJECT, 2022
** libmy
** File description:
** String module header
*/

#pragma once

char **my_strsplit_many(const char *str, const char *list);

char *my_revstr(const char *str);
char *my_strrep(const char *str, const char *pattern, const char *new);
char **my_strsplit(const char *str, char separator);
char *my_substr(const char *str, int start, int end);
char *my_substr_size(const char *str, size_t start, size_t end, size_t size);

char *my_timestr(void);
