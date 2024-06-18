/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** pfk
*/

#include "server.h"

void pfk(server_t *srv, connection_t *cl, player_t *player)
{
    queue_formatted_message(cl, "pfk #%d\n", player->id);
}