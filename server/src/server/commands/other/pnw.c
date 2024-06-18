/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** pnw
*/

#include "server.h"

void pnw(server_t *srv, connection_t *cl, player_t *player)
{
    queue_formatted_message(cl, "pnw %d %d %d %d %d %s\n", player->id,
        player->square->pos_x, player->square->pos_y, player->direction, player->level,
        player->team);
}
