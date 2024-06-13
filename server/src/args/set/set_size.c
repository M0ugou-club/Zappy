/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** set_coordinate
*/

#include "server.h"

int set_x(args_t *args, char **argv, int *i, int argc)
{
    if (*i + 1 >= argc)
        return EXIT_ERROR;
    args->x = atoi(argv[*i + 1]);
    return EXIT_SUCCESS;
}

int set_y(args_t *args, char **argv, int *i, int argc)
{
    if (*i + 1 >= argc)
        return EXIT_ERROR;
    args->y = atoi(argv[*i + 1]);
    return EXIT_SUCCESS;
}
