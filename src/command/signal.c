/*
** EPITECH PROJECT, 2021
** minishell2
** File description:
** Signals
*/

#include <signal.h>
#include <stdio.h>

void handle_quit(int sig)
{
    (void) sig;
    printf("\n$> ");
}

void init_signals(void)
{
    signal(SIGINT, &handle_quit);
}
