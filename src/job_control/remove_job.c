/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Remove case if there is zombie job
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include "types.h"
#include "jobs.h"

char **remove_incorrect_char(char **input)
{
    for (int i = 0; input[i] != NULL; i++) {
        if (job_command_case(input[i])) {
            input[i] = NULL;
            return (input);
        }
    }
    return (input);
}
