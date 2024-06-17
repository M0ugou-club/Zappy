/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** pin
*/

#include "server.h"

void pin(server_t *srv, connection_t *cl)
{
    player_t *player = get_player_by_fd(srv->game->players, cl->fd);

    queue_formatted_message(cl, "pin #%d %d %d %d %d %d %d %d %d %d\n",
        player->id, player->pos.x, player->pos.y, player->inventory->food,
        player->inventory->linemate, player->inventory->deraumere,
        player->inventory->sibur, player->inventory->mendiane,
        player->inventory->phiras, player->inventory->thystame);
}

// Send the player's inventory
void cmd_pin(server_t *srv, connection_t *cl, regex_parse_t *parse)
{
    return;
}
