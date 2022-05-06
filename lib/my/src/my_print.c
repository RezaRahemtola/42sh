/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** printing functions
*/

#include <unistd.h>
#include "my_math.h"
#include "my_string.h"
#include "my.h"

void my_putchar(char c)
{
    write(1, &c, 1);
}

void my_putstr(char const *str)
{
    int size = my_strlen(str);

    write(1, str, size);
}

void my_putnbr(int nb)
{
    int size = my_nbrlen(nb);
    int pow = 0;
    int number = 0;

    if (nb < 0) {
        size--;
        nb = -nb;
        my_putchar('-');
    }
    for (int i = size; i > 0; i--) {
        pow = my_power(10, i - 1);
        number = nb / pow % 10;
        my_putchar(ITOC(number));
    }
}
