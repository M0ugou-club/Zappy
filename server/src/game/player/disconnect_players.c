/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** disconnect_players
*/

#include "server.h"

void disconnect_players(server_t *srv)
{
    connection_t *tmp = srv->cons;
    player_t *ply = NULL;

    while (tmp != NULL) {
        ply = get_player_by_fd(srv->game->players, tmp->fd);
        if (ply != NULL && ply->disconnect == true) {
            remove_connection(&srv->cons, tmp->fd);
            broadcast_gui(srv, "pdi %d\n", ply->id);
            remove_player(&srv->game->players, ply->fd);
            return;
        }
        tmp = tmp->next;
    }
}
