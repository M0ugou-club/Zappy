/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** pgt
*/

#include "server.h"

void pgt(server_t *srv, connection_t *cl, player_t *player, int res)
{
    queue_formatted_message(cl, "pgt %d %d\n", player->id, res);
}
