/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** init_server
*/

#include "server.h"

static bool find_errors(server_t *srv)
{
    if (srv == NULL)
        return true;
    if (srv->sock == NULL)
        return true;
    if (srv->game == NULL)
        return true;
    if (srv->readfds == NULL)
        return true;
    if (srv->writefds == NULL)
        return true;
    return false;
}

server_t *init_server(args_t *args)
{
    server_t *server = malloc(sizeof(server_t));

    server->args = args;
    server->sock = init_socket(args->port);
    server->cons = NULL;
    server->close = false;
    server->game = init_game(args->x, args->y, args->teams, args);
    server->readfds = malloc(sizeof(fd_set));
    server->writefds = malloc(sizeof(fd_set));
    FD_ZERO(server->readfds);
    FD_ZERO(server->writefds);
    if (find_errors(server)) {
        if (server->sock)
            free_socket(server->sock);
        if (server->game)
            free_game(server->game);
        free(server->readfds);
        free(server->writefds);
        free(server);
        return (NULL);
    }
    return (server);
}
