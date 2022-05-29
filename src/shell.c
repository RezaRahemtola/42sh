/*
** EPITECH PROJECT, 2021
** 42sh
** File description:
** Shell
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell.h"
#include "environment.h"
#include "jobs.h"

bool compare_pid(void *list_elem, void *compare)
{
    job_t *old = list_elem;

    (void)compare;
    if (kill(old->pid, SIGCHLD) < 0) {
        return (true);
    } else {
        return (false);
    }
}

void free_pid(void *elem)
{
    job_t *job = elem;

    printf("[%d] Done -> %s\n", job->nb_job, job->command);
    free(job->command);
    free(job);
}

int start_shell(const char *const *env)
{
    shell_t shell = {0, 0, 0, NULL};
    env_t *list = NULL;

    setbuf(stdout, NULL);
    setbuf(stderr, NULL);
    if (env == NULL) {
        fprintf(stderr, "Error: Invalid environment.\n");
        return (EXIT_USAGE);
    }
    list = get_env_from_array(env);
    remove_env_property(&list, "OLDPWD");
    init_signals();
    do_heartbeat(&list, &shell);
    destroy_env(list);
    return (shell.ret);
}

void do_heartbeat(env_t **env, shell_t *shell)
{
    size_t size = 0;
    ssize_t read_size;
    char *line = NULL;

    while (!shell->exit) {
        if (isatty(0))
            printf("$> ");
        read_size = getline(&line, &size, stdin);
        if (read_size == -1)
            shell->exit = true;
        my_list_remove(&shell->job, NULL, compare_pid, free_pid);
        if (read_size > 1) {
            handle_input(line, env, shell);
        }
        free(line);
        line = NULL;
    }
    if (isatty(0))
        printf("exit\n");
}
