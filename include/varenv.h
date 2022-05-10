/*
** EPITECH PROJECT, 2022
** minishell2
** File description:
** Varenv header
*/

#pragma once

#include "types.h"

varenv_t *varenv_get(varenv_t *list, char const *key);
void varenv_put(varenv_t **list, char *key, char *value);
void varenv_replace(varenv_t *list, char *key, char *value);
void varenv_remove(varenv_t **list, char *key);
int varenv_size(varenv_t *list);

void print_env(varenv_t *env);
void destroy_env(varenv_t *env);

void add_variable(varenv_t **env, char *key, char *value);
int set_variable(varenv_t **env, char *key, char *value);

char *extract_key(char const *var);
char *extract_value(char const *var);

char **convert_varenv(varenv_t *list);
varenv_t *convert_env(char **env);
