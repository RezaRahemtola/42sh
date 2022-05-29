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
    sigaction(SIGINT, &sa, NULL);
}
