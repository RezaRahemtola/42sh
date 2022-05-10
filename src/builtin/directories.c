/*
** EPITECH PROJECT, 2021
** minishell2
** File description:
** Directory manipulations
*/

#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "minishell.h"
#include "varenv.h"

int check_directory(char *path)
{
    struct stat stats;
    int st = stat(path, &stats);

    if (st != -1 && S_ISDIR(stats.st_mode)) {
        fprintf(stderr, "%s: Permission denied.\n", path);
        return (1);
    } else {
        return (0);
    }
}

void handle_cd(varenv_t **env, char *path)
{
    int size = strlen(path);

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

    if (strlen(path) > 1) {
        fprintf(stderr, "Usage: cd [-plvn][-|<dir>].\n");
    } else if (oldpwd == NULL) {
        fprintf(stderr, ": No such file or directory.\n");
    } else {
        change_dir(oldpwd->value);
    }
}

void change_dir(char *dir)
{
    struct stat stats;
    int st = stat(dir, &stats);

    if (st != -1 && !S_ISDIR(stats.st_mode)) {
        fprintf(stderr, "%s: Not a directory.\n", dir);
    } else if (chdir(dir) == -1) {
        fprintf(stderr, "%s: No such file or directory.\n", dir);
    }
}
