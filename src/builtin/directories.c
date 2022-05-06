/*
** EPITECH PROJECT, 2021
** minishell2
** File description:
** Directory manipulations
*/

#include <sys/stat.h>
#include <unistd.h>
#include "minishell.h"
#include "my_string.h"
#include "my.h"
#include "varenv.h"

int check_directory(char *path)
{
    struct stat stats;
    int st = stat(path, &stats);

    if (st != -1 && S_ISDIR(stats.st_mode)) {
        my_dprintf(2, "%s: Permission denied.\n", path);
        return (1);
    } else {
        return (0);
    }
}

void handle_cd(varenv_t **env, char *path)
{
    int size = my_strlen(path);

    if (size > 0 && path[0] == '-') {
        handle_prev(env, path);
    } else if (size > 0 && path[0] == '~') {
        handle_home(env, path);
    } else {
        change_dir(path);
    }
}

void handle_prev(varenv_t **env, char *path)
{
    varenv_t *oldpwd = varenv_get(*env, "OLDPWD");

    if (my_strlen(path) > 1) {
        my_dprintf(2, "Usage: cd [-plvn][-|<dir>].\n");
    } else if (oldpwd == NULL) {
        my_dprintf(2, ": No such file or directory.\n");
    } else {
        change_dir(oldpwd->value);
    }
}

void change_dir(char *dir)
{
    struct stat stats;
    int st = stat(dir, &stats);

    if (st != -1 && !S_ISDIR(stats.st_mode)) {
        my_dprintf(2, "%s: Not a directory.\n", dir);
    } else if (chdir(dir) == -1) {
        my_dprintf(2, "%s: No such file or directory.\n", dir);
    }
}
