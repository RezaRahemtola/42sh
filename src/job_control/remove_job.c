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

static bool compare_pid(void *list_elem, void *compare)
{
    job_t *old = list_elem;
    job_t *new = compare;

    if (new->pid == old->pid) {
        return (true);
    }
    else {
        return (false);
    }
}

static void free_pid(void *elem)
{
    job_t *job = elem;

    printf("[%d] Done -> %s\n", job->nb_job, job->command);
    free(job->command);
    free(job);
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
        if (tmp->pid != 0 && kill(tmp->pid, SIGCHLD) < 0) {
            my_list_remove(&job, tmp, compare_pid, free_pid);
        }
        tmp = tmp->next;
    }
    return (job);
}
