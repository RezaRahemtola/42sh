/*
** EPITECH PROJECT, 2021
** minishell2
** File description:
** Main
*/

#include "minishell.h"

int main(int argc, const char *argv[], char **env)
{
    (void) argc;
    (void) argv;
    return (start_minishell(env));
}
