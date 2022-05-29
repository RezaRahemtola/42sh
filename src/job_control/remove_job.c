/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Remove case if there is zombie job
*/

#include "types.h"
#include <stdio.h>
#include <stdlib.h>

job_t *remove_job(job_t *command, char *input)
{
    job_t *tmp = NULL;
    job_t *new_elem = NULL;

    new_elem = malloc(sizeof(job_t));
    new_elem->command = strdup(input);;
    new_elem->nb_job = 1;
    new_elem->next = NULL;
    if (command == NULL) {
        command = new_elem;
    } else {
        tmp = command;
        new_elem->nb_job++;
        for (tmp = command; tmp->next != NULL; ++new_elem->nb_job)
            tmp = tmp->next;
        tmp->next = new_elem;
    }
    return (command);
}

job_t *check_children(job_t *job)
{
    job_t *tmp = job;

    while (tmp != NULL) {
        if (kill(tmp->pid, SIGCHLD) <= 0)
            printf("[%d] Done -> %s\n", tmp->nb_job, tmp->command);
        tmp = tmp->next;
    }
}
