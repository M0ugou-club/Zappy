/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** fork
*/

#include "server.h"

// Lay an egg to allow a player to join the game
void cmd_fork(server_t *srv, connection_t *cl, regex_parse_t *parse)
{
    player_t *ply = get_player_by_fd(srv->game->players, cl->fd);

    add_egg(ply->square, ply->team);
    queue_message(cl, "ok\n");
}
