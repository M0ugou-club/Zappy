/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** pex
*/

#include "server.h"

void pex(server_t *srv, connection_t *cl, player_t *player)
{
    queue_formatted_message(cl, "pex #%d\n", player->id);
}