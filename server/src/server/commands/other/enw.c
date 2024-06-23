/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** enw
*/

#include "server.h"

void enw(server_t *srv, connection_t *cl, egg_t *egg, player_t *player)
{
    queue_formatted_message(cl, "enw %d %d %d %d\n", egg->id, player->id,
        player->square->pos_x, player->square->pos_y);
}
