/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Remove case if there is zombie job
*/

#include "types.h"
#include <stdio.h>

void check_zombie(job_t *job)
{
    job_t *tmp = job;

    while (tmp != NULL) {
        tmp = tmp->next;
    }
}
