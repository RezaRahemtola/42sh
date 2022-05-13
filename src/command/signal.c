/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Signals
*/

#include <signal.h>
#include <stdio.h>

void handle_quit(__attribute__ ((unused)) int sig)
{
    printf("\n$> ");
}

void init_signals(void)
{
    signal(SIGINT, &handle_quit);
}
