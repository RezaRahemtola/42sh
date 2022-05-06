/*
** EPITECH PROJECT, 2022
** libmy
** File description:
** Infinite module header
*/

#pragma once

char *my_inf_getnbr(char const *str);
char *my_inf_getnbr_base(char const *str, char const *base);
char *my_inf_parsenbr_base(char const *nbr, char const *base);
int my_inf_cmp(char const *nbr1, char const *nbr2);

char *my_infinadd(char const *nbr1, char const *nbr2);
char *my_infinsub(char const *nbr1, char const *nbr2);
char *my_infinmult(char const *nbr1, char const *nbr2);
char *my_infindiv(char const *nbr1, char const *nbr2);
char *my_infinmod(char const *nbr1, char const *nbr2);

char *my_inf_abs(char const *nbr);
char *my_inf_log(char const *nbr, char const *x);
char *my_inf_opposite(char const *nbr);
char *my_inf_power(char *nbr, char *p);
