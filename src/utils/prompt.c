/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Functions to display the prompt
*/

#include <unistd.h>
#include <stdio.h>

void display_prompt(void)
{
    if (isatty(0))
        printf("$> ");
}
