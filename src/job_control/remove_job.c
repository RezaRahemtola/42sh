/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Remove case if there is zombie job
*/

#include <stdio.h>
#include <stdlib.h>
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

list_t *check_children(list_t *job)
{
    job_t *tmp = NULL;
    job_t *new = NULL;

    if (job != NULL && job->data != NULL) {
        tmp = job->data;
        new = job->data;
    }
    while (tmp != NULL) {
        if (kill(tmp->pid, SIGCHLD) < 0) {
            printf("[%d] Done -> %s\n", tmp->nb_job, tmp->command);
        }
        tmp = tmp->next;
    }
    return (job);
}
