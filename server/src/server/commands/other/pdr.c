/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** pdr
*/

#include "server.h"

void pdr(server_t *srv, connection_t *cl, player_t *player, int res)
{
    queue_formatted_message(cl, "pdr #%d %d\n", player->id, res);
}
