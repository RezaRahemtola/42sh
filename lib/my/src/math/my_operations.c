/*
** EPITECH PROJECT, 2021
** libmy
** File description:
** Math operations
*/

static int factorial_rec(int nbr)
{
    if (nbr == 0) {
        return (1);
    } else if (nbr < 0) {
        return (0);
    } else {
        return (nbr * factorial_rec(nbr - 1));
    }
}

int my_factorial(int nbr)
{
    int total = 0;

    if (nbr < 13) {
        total = factorial_rec(nbr);
    }
    return (total);
}

int my_log(int nbr, int x)
{
    int result = 0;

    if (nbr < 1 || x < 1) {
        return (0);
    }
    for (int i = 0; nbr >= x; i++) {
        result++;
        nbr /= x;
    }
    return (result);
}

int my_llog(long lnbr, int x)
{
    int result = 0;

    if (lnbr < 1 || x < 1) {
        return (0);
    }
    for (int i = 0; lnbr >= x; i++) {
        result++;
        lnbr /= x;
    }
    return (result);
}
