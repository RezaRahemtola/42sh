/*
** EPITECH PROJECT, 2022
** libmy
** File description:
** String module header
*/

#pragma once

#include <stdbool.h>

int my_strlen(char const *str);
char *my_strdup(char const *str);
char *my_stringify(char c);

int my_strcmp(char const *str1, char const *str2);
int my_strncmp(char const *str1, char const *str2, int nbr);

bool my_str_contains(char const *str, char const *pattern);
bool my_str_containsany(char const *str, char const *list);
bool my_str_containsonly(char const *str, char const *list);
bool my_str_containschar(char const *str, char c);
bool my_str_starts(char const *str, char const *pattern);

bool my_str_isalpha(char const *str);
bool my_str_islower(char const *str);
bool my_str_isnum(char const *str);
bool my_char_isalpha(char c);
bool my_str_isupper(char const *str);


int my_strtoi(char **ptr);
char **my_strsplit_many(char const *str, char const *list);

char *my_revstr(char const *str);
char *my_revxstr(char *str);
char *my_strxcapitalize(char *str);
char *my_strcapitalize(char const *str);
char *my_strcat(char const *, char const *);
char *my_strcpy(char *, char const *);
char *my_strlowcase(char *);
char *my_strncat(char *, char const *, int);
char *my_strncpy(char *, char const *, int);
char *my_strrep(char *, char const *, char const *);
char **my_strsplit(char const *, char);
char *my_strstr(char *, char const *);
char *my_strupcase(char *);
char *my_substr(char const *, int, int);
char *my_substr_size(char const *, int, int, int);
void my_strfill(char *, int, char);
void my_strxcat(char *, char *, int);
