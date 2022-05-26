/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Functions to load initial localenv values
*/

#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>
#include <stdlib.h>
#include <stdio.h>
#include "environment.h"

static void add_uid_var(uid_t id, const char *key, shell_t *shell)
{
    size_t id_len = snprintf(NULL, 0, "%d", id) + 1;
    char *value = malloc(sizeof(char) * id_len);

    snprintf(value, id_len, "%d", id);
    add_localvar(&shell->localenv, key, value, false);
    free(value);
}

void load_localenv(shell_t *shell)
{
    uid_t euid = geteuid();
    uid_t uid = getuid();
    struct passwd *epw = getpwuid(euid);
    struct passwd *pw = getpwuid(uid);

    add_uid_var(euid, "euid", shell);
    add_localvar(&shell->localenv, "euser", epw->pw_name, false);
    add_localvar(&shell->localenv, "home", pw->pw_dir, false);
    add_uid_var(uid, "uid", shell);
    add_localvar(&shell->localenv, "user", pw->pw_name, false);
}
