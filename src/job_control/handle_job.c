/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Handle job control
*/

#include <stdbool.h>
#include <stdio.h>
#include "shell.h"

bool job_command_case(char *command)
{
    for (int i = 0; command[i] != '\0'; i++) {
        if (command[i] == '&') {
            return (true);
        }
    }
    return (false);
}

char *remove_incorrect_char(char *input)
{
    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] == '&') {
            input[i] = '\0';
            return (input);
        }
    }
    return (input);
}

job_t *add_new_job(job_t *command, char *input)
{
    job_t *tmp = NULL;
    job_t *new_elem = NULL;

    new_elem = malloc(sizeof(job_t));
    new_elem->command = strdup(input);
    new_elem->nb_job = 1;
    new_elem->next = NULL;
    if (command == NULL) {
        printf("add: [%d] %s\n", new_elem->nb_job, new_elem->command);
        command = new_elem;
    } else {
        tmp = command;
        new_elem->nb_job++;
        for (tmp = command; tmp->next != NULL; new_elem->nb_job++)
            tmp = tmp->next;
        printf("add: [%d] %s\n", new_elem->nb_job, new_elem->command);
        tmp->next = new_elem;
    }
    return (command);
}

job_t *add_job_pid(job_t *job, char *wanted, pid_t pid)
{
    job_t *tmp = job;

    while (tmp != NULL) {
        if (!strcmp(wanted, tmp->command)) {
            tmp->pid = pid;
            printf("[%d] %d\n", tmp->nb_job, tmp->pid);
            return (job);
        }
        tmp = tmp->next;
    }
    return (job);
}

void check_zombie(job_t *job)
{
    job_t *tmp = job;

    while (tmp != NULL) {
        tmp = tmp->next;
    }
}
