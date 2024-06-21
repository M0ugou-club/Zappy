/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** pdi
*/

#include "server.h"

void pdi(server_t *srv, connection_t *cl, player_t *player)
{
    queue_formatted_message(cl, "pdi #%d\n", player->id);
}
