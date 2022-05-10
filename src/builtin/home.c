/*
** EPITECH PROJECT, 2022
** minishell2
** File description:
** Home alias functions
*/

#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "builtin.h"
#include "minishell.h"
#include "my_string.h"
#include "varenv.h"

void handle_home(varenv_t **env, char *path)
{
    char *result = NULL;
    varenv_t *home = varenv_get(*env, "HOME");

    if (home == NULL) {
        fprintf(stderr, "No $home variable set.\n");
    } else if (strlen(path) == 1) {
        change_home(env);
    } else {
        result = my_strrep(path, "~", home->value);
        change_dir(result);
        free(result);
    }
}

void change_home(varenv_t **env)
{
    varenv_t *home = varenv_get(*env, "HOME");
    struct stat stats;
    int st = stat((home == NULL ? "" : home->value), &stats);
    int file = (st != -1 && !S_ISDIR(stats.st_mode));

    if (home == NULL) {
        fprintf(stderr, "cd: No home directory.\n");
    } else if (chdir(home->value) == -1 || file) {
        fprintf(stderr, "cd: Can't change to home directory.\n");
    }
}

void s_handle_home(varenv_t **env, char *path, minishell_t *shell, \
char *current)
{
    char *result = NULL;
    varenv_t *home = varenv_get(*env, "HOME");

    if (home == NULL) {
        shell->ret = 1;
    } else if (strlen(path) == 1) {
        s_change_home(env, shell, current);
    } else {
        result = my_strrep(path, "~", home->value);
        s_change_dir(env, shell, result, current);
        free(result);
    }
}

void s_change_home(varenv_t **env, minishell_t *shell, char *current)
{
    varenv_t *home = varenv_get(*env, "HOME");
    struct stat stats;
    int st = stat((home == NULL ? "" : home->value), &stats);
    int file = (st != -1 && !S_ISDIR(stats.st_mode));

    if (home == NULL) {
        shell->ret = 1;
    } else if (chdir(home->value) == -1 || file) {
        shell->ret = 1;
    } else {
        shell->ret = 0;
        add_variable(env, "PWD", home->value);
        add_variable(env, "OLDPWD", current);
    }
}

bool is_builtin(char *command)
{
    if (command == NULL) {
        return (false);
    }
    for (int i = 0; BUILTIN[i].command != NULL; i++) {
        if (strcmp(command, BUILTIN[i].command) == 0) {
            return (true);
        }
    }
    return (false);
}
