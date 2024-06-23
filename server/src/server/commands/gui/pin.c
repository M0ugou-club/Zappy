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

    queue_formatted_message(cl, "pin %d %d %d %d %d %d %d %d %d %d\n",
        player->id, player->square->pos_x,
        player->square->pos_y, player->inventory[0],
        player->inventory[1], player->inventory[2], player->inventory[3],
        player->inventory[4], player->inventory[5], player->inventory[6]);
}

// Send the player's inventory
void cmd_pin(server_t *srv, connection_t *cl, regex_parse_t *parse)
{
    pin(srv, cl);
}
