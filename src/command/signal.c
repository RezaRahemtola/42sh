/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Signals
*/

#include <signal.h>
#include <stdio.h>
#include "graphics.h"

void handle_quit(__attribute__ ((unused)) int sig)
{
    char *prompt = get_prompt();

    if (prompt)
        printf("\n%s", prompt);
}

void init_signals(void)
{
    signal(SIGINT, &handle_quit);
}
