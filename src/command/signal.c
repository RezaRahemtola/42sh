/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Signals
*/

#include <signal.h>
#include <stdio.h>
#include "graphics.h"

static void handler(int sig)
{
    if (sig == SIGINT) {
        printf("\n%s", get_prompt());
    }
}

void init_signals(void)
{
    struct sigaction sa;

    sigemptyset(&sa.sa_mask);
    sa.sa_handler = handler;
    sa.sa_flags = SA_RESTART | SA_NOCLDWAIT;
    //sigaction(SIGCHLD, &sa, NULL);
    sigaction(SIGINT, &sa, NULL);
}
