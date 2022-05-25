/*
** EPITECH PROJECT, 2022
** 42sh
** File description:
** Environment header
*/

#pragma once

#include "types.h"

const env_t *get_env_value(const env_t *list, const char *key);
void put_env_property(env_t **list, const char *key, const char *value);
void replace_env_value(env_t *list, const char *key, const char *value);
void remove_env_property(env_t **list, const char *key);
size_t get_env_size(const env_t *list);

void print_env(const env_t *env);
void destroy_env(env_t *env);

void add_variable(env_t **env, const char *key, const char *value);

char *extract_env_key(const char *var);
char *extract_env_value(const char *var);

char *const *get_array_from_env(const env_t *list);
env_t *get_env_from_array(const char *const *env);

// Localenv
const localenv_t *get_localenv_value(const localenv_t *list, const char *key);
void put_localenv_property(localenv_t **list, const char *key,
const char *value, bool readonly);
void replace_localenv_value(localenv_t *list, const char *key,
const char *value, bool readonly);
void remove_localenv_property(localenv_t **list, const char *key);
size_t get_localenv_size(const localenv_t *list);

void print_localenv(const localenv_t *env);
void destroy_localenv(localenv_t *env);

void add_localvar(localenv_t **env, const char *key, const char *value,
bool readonly);
int set_localvar(localenv_t **env, const char *key, const char *value,
bool readonly);
