/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Main
*/

#include "shell.h"

int main(int argc, const char *argv[], const char *const *env)
{
    (void) argc;
    (void) argv;
    return (start_shell(env));
}
