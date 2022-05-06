/*
** EPITECH PROJECT, 2022
** libmy
** File description:
** Math module header
*/

#pragma once

#include <stdbool.h>

int my_nbrlen(int nbr);
int my_lnbrlen(long lnbr);
int my_getnbr(char const *str);
int my_getnbr_base(char const *str, char const *base);
char *my_parsenbr(int nbr);
char *my_parsenbr_base(int nbr, char const *base);
char *my_parsenbr_long(long long lnbr);
bool my_is_number(char *str);
char *my_number(char **str);

int my_factorial(int nbr);
int my_log(int nbr, int log);
int my_llog(long lnbr, int log);
int my_power(int nbr, int power);
int my_square_root(int nbr);
bool my_is_prime(int nbr);
int my_find_prime_sup(int nbr);
