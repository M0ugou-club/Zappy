/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** pbc
*/

#include "server.h"

void pbc(server_t *srv, connection_t *cl, player_t *player, char *msg)
{
    queue_formatted_message(cl, "pbc #%d %s\n", player->id, msg);
}
