/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** plv
*/

#include "server.h"

void plv(server_t *srv, connection_t *cl)
{
    player_t *player = get_player_by_fd(srv->game->players, cl->fd);

    queue_formatted_message(cl, "plv #%d %d\n", player->id, player->level);
}

// Send the player's level
void cmd_plv(server_t *srv, connection_t *cl, regex_parse_t *parse)
{
    plv(srv, cl);
}
