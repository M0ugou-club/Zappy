/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** get_args
*/

#include "server.h"
#include <stdbool.h>

static const arg_match_t arg_match[] = {
    {"-p", &set_port},
    {"-x", &set_x},
    {"-y", &set_y},
    {"-n", &set_teams},
    {"-c", &set_max_clients},
    {"-f", &set_frequency},
    {NULL, NULL}
};

static bool check_arg(args_t *args, const arg_match_t *arg_match, int i,
    main_args_t *main_args)
{
    if (strcmp(main_args->argv[i], arg_match->arg) == 0)
        if (arg_match->func(args, main_args->argv, &i, main_args->argc)
            == EXIT_ERROR)
            return false;
    return true;
}

static bool check_match(args_t *args, char **argv, int i, int argc)
{
    main_args_t m_args = {argc, argv};

    for (int j = 0; arg_match[j].arg != NULL; j++) {
        if (!check_arg(args, &arg_match[j], i, &m_args))
            return false;
    }
    return true;
}

args_t *get_args(int argc, char **argv)
{
    args_t *args = malloc(sizeof(args_t));

    if (args == NULL)
        return NULL;
    memset(args, 0, sizeof(args_t));
    for (int i = 1; i < argc; i++) {
        if (!check_match(args, argv, i, argc))
            return NULL;
    }
    return args;
}
