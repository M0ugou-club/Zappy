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

static server_t *free_internal(server_t *srv)
{
    if (srv->sock)
        free_socket(srv->sock);
    if (srv->game)
        free_game(srv->game);
    free(srv->readfds);
    free(srv->writefds);
    free(srv);
    return (NULL);
}

server_t *init_server(args_t *args)
{
    server_t *srv = malloc(sizeof(server_t));

    srv->args = args;
    srv->sock = init_socket(args->port);
    srv->cons = NULL;
    srv->close = false;
    srv->game = init_game(args->x, args->y, args->teams, args);
    srv->readfds = malloc(sizeof(fd_set));
    srv->writefds = malloc(sizeof(fd_set));
    FD_ZERO(srv->readfds);
    FD_ZERO(srv->writefds);
    if (find_errors(srv))
        return free_internal(srv);
    return (srv);
}
