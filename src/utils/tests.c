/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Variables tests
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "builtin.h"
#include "my_string.h"
#include "my.h"

static char *return_value(shell_t *shell)
{
    size_t id_len = snprintf(NULL, 0, "%d", shell->ret) + 1;
    char *value = malloc(sizeof(char) * id_len);

    snprintf(value, id_len, "%d", shell->ret);
    return (value);
}

static void replace_value(command_t *command, char *name, char *value, size_t i)
{
    char *input = malloc(sizeof(char) * (strlen(value) + 3));
    char *replaced = NULL;

    if (input == NULL)
        return;
    strcpy(input, "$?");
    strcat(input, name);
    replaced = my_strrep(command->args[i], input, value);
    if (replaced == NULL) {
        free(input);
        return;
    }
    replace_argument(command, i, replaced);
    free(input);
}


void replace_test(command_t *command, shell_t *shell, size_t i)
{
    bool ret = false;
    size_t size = strlen(command->args[i]);
    char *name = get_variable_name(command->args[i], 2, size);
    char *value = NULL;
    char *rep = NULL;

    if (name == NULL)
        return;
    ret = (strlen(name) == 0);
    value = (ret ? return_value(shell) : env_value(shell, name));
    rep = (value != NULL ? strdup("1") : strdup("0"));
    replace_value(command, name, (ret ? value : rep), i);
    my_free(2, name, rep);
    if (value != NULL)
        free(value);
}
