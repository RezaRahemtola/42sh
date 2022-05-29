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
    (void)sig;
    printf("\n%s", get_prompt());
}

void init_signals(void)
{
    signal(SIGINT, &handler);
}
