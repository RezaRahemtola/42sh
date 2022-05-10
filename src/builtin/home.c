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
#include "builtin.h"
#include "minishell.h"
#include "my_string.h"
#include "my.h"
#include "varenv.h"

void handle_home(varenv_t **env, char *path)
{
    char *result = NULL;
    varenv_t *home = varenv_get(*env, "HOME");

    if (home == NULL) {
        my_dprintf(2, "No $home variable set.\n");
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
        my_dprintf(2, "cd: No home directory.\n");
    } else if (chdir(home->value) == -1 || file) {
        my_dprintf(2, "cd: Can't change to home directory.\n");
    }
}

int s_handle_home(varenv_t **env, char *path, char *current)
{
    int ret = 0;
    char *result = NULL;
    varenv_t *home = varenv_get(*env, "HOME");

    if (home == NULL) {
        return (1);
    } else if (strlen(path) == 1) {
        return (s_change_home(env, current));
    } else {
        result = my_strrep(path, "~", home->value);
        ret = s_change_dir(env, result, current);
        free(result);
        return (ret);
    }
}

int s_change_home(varenv_t **env, char *current)
{
    varenv_t *home = varenv_get(*env, "HOME");
    struct stat stats;
    int st = stat((home == NULL ? "" : home->value), &stats);
    int file = (st != -1 && !S_ISDIR(stats.st_mode));

    if (home == NULL || chdir(home->value) == -1 || file) {
        return (1);
    } else {
        add_variable(env, "PWD", home->value);
        add_variable(env, "OLDPWD", current);
        return (0);
    }
}

bool is_builtin(char *command)
{
    if (command == NULL) {
        return (false);
    }
    for (int i = 0; BUILTIN[i].command != NULL; i++) {
        if (my_strcmp(command, BUILTIN[i].command) == 0) {
            return (true);
        }
    }
    return (false);
}
