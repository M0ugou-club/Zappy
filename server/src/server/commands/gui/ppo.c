/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** ppo
*/

#include "server.h"

void ppo(server_t *srv, connection_t *cl)
{
    player_t *player = get_player_by_fd(srv->game->players, cl->fd);

    queue_formatted_message(cl, "ppo #%d %d %d %d\n", player->id,
        player->square->pos_x, player->square->pos_y, player->direction);
}

// Send the player's position
void cmd_ppo(server_t *srv, connection_t *cl, regex_parse_t *parse)
{
    ppo(srv, cl);
}
