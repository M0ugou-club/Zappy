/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** init_server
*/

#include "server.h"

server_t *init_server(args_t *args)
{
    server_t *server = malloc(sizeof(server_t));

    server->args = args;
    server->sock = init_socket(args->port);
    server->cons = NULL;
    server->game = init_game(args->x, args->y, args->teams);
    server->readfds = malloc(sizeof(fd_set));
    server->writefds = malloc(sizeof(fd_set));
    server->exceptfds = malloc(sizeof(fd_set));
    FD_ZERO(server->readfds);
    FD_ZERO(server->writefds);
    FD_ZERO(server->exceptfds);
    return (server);
}
