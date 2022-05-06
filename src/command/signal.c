/*
** EPITECH PROJECT, 2021
** minishell2
** File description:
** Signals
*/

#include <signal.h>
#include "minishell.h"
#include "my.h"

void init_signals(void)
{
    signal(SIGINT, &handle_quit);
}

void handle_quit(int sig)
{
    (void) sig;
    my_printf("\n$> ");
}
