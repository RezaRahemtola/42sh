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

void s_handle_cd(varenv_t **env, char *path, minishell_t *shell, char *current)
{
    int size = strlen(path);

    if (size > 0 && path[0] == '-') {
        s_handle_prev(env, path, shell, current);
    } else if (size > 0 && path[0] == '~') {
        s_handle_home(env, path, shell, current);
    } else {
        s_change_dir(env, shell, path, current);
    }
}

void s_handle_prev(varenv_t **env, char *path, minishell_t *shell, \
char *current)
{
    varenv_t *oldpwd = varenv_get(*env, "OLDPWD");

    if (my_strlen(path) > 1) {
        shell->ret = 1;
    } else if (oldpwd == NULL) {
        shell->ret = 1;
    } else {
        s_change_dir(env, shell, oldpwd->value, current);
    }
}

void s_change_dir(varenv_t **env, minishell_t *shell, char *dir, char *current)
{
    struct stat stats;
    int st = stat(dir, &stats);

    if (st != -1 && !S_ISDIR(stats.st_mode)) {
        shell->ret = 1;
    } else if (chdir(dir) == -1) {
        shell->ret = 1;
    } else {
        shell->ret = 0;
        add_variable(env, "PWD", dir);
        add_variable(env, "OLDPWD", current);
    }
}
