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
    char *prompt = get_prompt();

    (void) sig;
    if (prompt)
        printf("\n%s", prompt);
}

void init_signals(void)
{
    signal(SIGINT, &handler);
}
