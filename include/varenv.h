/*
** EPITECH PROJECT, 2022
** minishell2
** File description:
** Varenv header
*/

#pragma once

#include "types.h"

varenv_t *varenv_get(varenv_t *list, const char *key);
void varenv_put(varenv_t **list, const char *key, const char *value);
void varenv_replace(varenv_t *list, const char *key, const char *value);
void varenv_remove(varenv_t **list, const char *key);
int varenv_size(varenv_t *list);

void print_env(varenv_t *env);
void destroy_env(varenv_t *env);

void add_variable(varenv_t **env, const char *key, const char *value);
int set_variable(varenv_t **env, const char *key, const char *value);

char *extract_key(const char *var);
char *extract_value(const char *var);

char **convert_varenv(varenv_t *list);
varenv_t *convert_env(char **env);
