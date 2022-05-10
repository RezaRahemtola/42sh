/*
** EPITECH PROJECT, 2021
** minishell2
** File description:
** Signals
*/

#include <signal.h>
#include <stdio.h>
#include "minishell.h"

void init_signals(void)
{
    signal(SIGINT, &handle_quit);
}

void handle_quit(int sig)
{
    (void) sig;
    printf("\n$> ");
}
