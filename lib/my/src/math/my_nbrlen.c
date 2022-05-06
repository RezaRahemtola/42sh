/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** my_nbrlen function
*/

int my_nbrlen(int nbr)
{
    int size = 1;

    if (nbr < 0) {
        size++;
    }
    nbr /= 10;
    while (nbr != 0) {
        nbr /= 10;
        size++;
    }
    return (size);
}

int my_lnbrlen(long lnbr)
{
    int size = 1;

    if (lnbr < 0) {
        size++;
    }
    lnbr /= 10;
    while (lnbr != 0) {
        lnbr /= 10;
        size++;
    }
    return (size);
}
