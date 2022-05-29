/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Signals
*/

#include <signal.h>
#include <stdio.h>
#include "types.h"

void catch_bg_signal(int sig)
{
    
}

static void handler(int sig)
{
    if (sig == SIGINT) {
        printf("\n$> ");
    }
}

void init_signals(void)
{
    struct sigaction sa;

    sigemptyset(&sa.sa_mask);
    sa.sa_handler = handler;
    sa.sa_flags = SA_RESTART | SA_NOCLDWAIT;
    sigaction(SIGCHLD, &sa, NULL);
    sigaction(SIGINT, &sa, NULL);
}
