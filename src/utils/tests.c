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

void replace_argument(command_t *command, size_t index, char *new_arg)
{
    char *replaced = my_strrep(command->input, command->args[index], new_arg);

    if (replaced == NULL)
        return;
    my_free(2, command->input, command->args[index]);
    command->input = replaced;
    command->args[index] = new_arg;
}

static char *return_value(const shell_t *shell)
{
    size_t id_len = snprintf(NULL, 0, "%d", shell->ret) + 1;
    char *value = malloc(sizeof(char) * id_len);

    snprintf(value, id_len, "%d", shell->ret);
    return (value);
}

static void replace_value(command_t *command, const char *name,
const char *value, size_t index)
{
    char *input = malloc(sizeof(char) * (strlen(value) + 3));
    char *replaced = NULL;

    if (input == NULL)
        return;
    sprintf(input, "$?%s", name);
    replaced = my_strrep(command->args[index], input, value);
    if (replaced == NULL) {
        free(input);
        return;
    }
    replace_argument(command, index, replaced);
    free(input);
}

void replace_test(command_t *command, shell_t *shell, size_t index, size_t i)
{
    bool ret = false;
    size_t size = strlen(command->args[index]);
    char *name = get_variable_name(command->args[index], i + 2, size);
    char *value = NULL;
    char *rep = NULL;

    if (name == NULL)
        return;
    ret = (strlen(name) == 0);
    value = (ret ? return_value(shell) : env_value(shell, name));
    rep = (value != NULL ? strdup("1") : strdup("0"));
    replace_value(command, name, (ret ? value : rep), index);
    my_free(2, name, rep);
    if (value != NULL)
        free(value);
}
