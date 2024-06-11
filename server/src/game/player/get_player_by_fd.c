/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** get_player_by_fd
*/

#include "server.h"
#include "game.h"

player_t *get_player_by_fd(connection_t *cl, server_t *srv)
{
    player_t *tmp = srv->game->players;

    while (tmp != NULL) {
        if (tmp->fd == cl->fd)
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}