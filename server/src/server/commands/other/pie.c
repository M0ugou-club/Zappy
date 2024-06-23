/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** pie
*/

#include "server.h"

void pie(server_t *srv, connection_t *cl, player_t *player, char *result)
{
    queue_formatted_message(cl, "pie %d %d %s\n", player->square->pos_x,
        player->square->pos_y, result);
}
