/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Functions to load initial localenv values
*/

#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "environment.h"

static void add_id_var(unsigned int id, const char *key, shell_t *shell)
{
    size_t id_len = snprintf(NULL, 0, "%d", id) + 1;
    char *value = malloc(sizeof(char) * id_len);

    snprintf(value, id_len, "%d", id);
    add_localvar(&shell->localenv, key, value, false);
    free(value);
}

static void add_user_variables(shell_t *shell)
{
    uid_t uid = getuid();
    struct passwd *pw = getpwuid(uid);
    struct group *group = NULL;

    if (pw != NULL) {
        group = getgrgid(pw->pw_gid);
        add_id_var(pw->pw_gid, "gid", shell);
        add_localvar(&shell->localenv, "group", group->gr_name, false);
        add_localvar(&shell->localenv, "history", "100", false);
        add_localvar(&shell->localenv, "home", pw->pw_dir, false);
        add_localvar(&shell->localenv, "owd", "", false);
        add_id_var(uid, "uid", shell);
        add_localvar(&shell->localenv, "user", pw->pw_name, false);
    }
}

void load_localenv(shell_t *shell)
{
    uid_t euid = geteuid();
    struct passwd *epw = getpwuid(euid);
    char *cwd = getcwd(NULL, 0);

    add_localvar(&shell->localenv, "cwd", cwd, false);
    if (epw != NULL) {
        add_id_var(euid, "euid", shell);
        add_localvar(&shell->localenv, "euser", epw->pw_name, false);
    }
    add_user_variables(shell);
    free(cwd);
}

void add_localvar(localenv_t **env, const char *key, const char *value,
bool readonly)
{
    const localenv_t *var = get_localenv_value(*env, key);

    if (var == NULL)
        put_localenv_property(env, key, value, readonly);
    else
        replace_localenv_value(*env, key, value, readonly);
}
