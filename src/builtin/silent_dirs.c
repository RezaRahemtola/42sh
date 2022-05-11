/*
** EPITECH PROJECT, 2022
** minishell2
** File description:
** Silent directory checks
*/

#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include "minishell.h"
#include "my_string.h"
#include "varenv.h"

int s_handle_cd(varenv_t **env, char *path, char *current)
{
    size_t size = strlen(path);

    if (size > 0 && path[0] == '-') {
        return (s_handle_prev(env, path, current));
    } else if (size > 0 && path[0] == '~') {
        return (handle_home_silently(env, path, current));
    } else {
        return (s_change_dir(env, path, current));
    }
}

int s_handle_prev(varenv_t **env, char *path, char *current)
{
    varenv_t *oldpwd = varenv_get(*env, "OLDPWD");

    if (my_strlen(path) > 1 || oldpwd == NULL) {
        return (1);
    } else {
        return (s_change_dir(env, oldpwd->value, current));
    }
}

int s_change_dir(varenv_t **env, char *dir, char *current)
{
    struct stat stats;
    int st = stat(dir, &stats);

    if (st == -1 || !S_ISDIR(stats.st_mode) || chdir(dir) == -1) {
        return (1);
    } else {
        add_variable(env, "PWD", dir);
        add_variable(env, "OLDPWD", current);
        return (0);
    }
}
