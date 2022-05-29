/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Graphics initialization
*/

#include <stdio.h>
#include <term.h>
#include <curses.h>
#include "environment.h"
#include "messages.h"

static void set_exit(shell_t *shell)
{
    shell->exit = true;
    shell->ret = 1;
}

static bool init_termcap(char const *term)
{
    int ret = tgetent(NULL, term);

    if (ret == -1) {
        fprintf(stderr, "%s\n", ERROR_TERM);
        return (false);
    } else if (ret == 0) {
        fprintf(stderr, "%s\n", UNKNOWN_TERM);
        return (false);
    }
    return (true);
}

static bool init_terminfo(char const *term)
{
    int ptr = 0;
    int ret = setupterm(term, 1, &ptr);

    if (ret == OK)
        return (true);
    if (ptr == -1)
        fprintf(stderr, "%s\n", ERROR_TERM);
    else
        fprintf(stderr, "%s\n", UNKNOWN_TERM);
    return (false);
}

void init_graphics(shell_t *shell)
{
    const env_t *term = get_env_value(shell->env, "TERM");

    if (term == NULL) {
        fprintf(stderr, "%s\n", NO_TERM);
        set_exit(shell);
        return;
    }
    if (!init_termcap(term->value)) {
        set_exit(shell);
        return;
    }
    if (!init_terminfo(term->value)) {
        set_exit(shell);
        return;
    }
}
