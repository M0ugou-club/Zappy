/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** eject
*/

#include "server.h"

static void eject_player(player_t *player)
{
    if (player->direction == NORTH) {
        player->square = player->square->south;
    } else if (player->direction == SOUTH) {
        player->square = player->square->north;
    } else if (player->direction == EAST) {
        player->square = player->square->west;
    } else if (player->direction == WEST) {
        player->square = player->square->east;
    }
}

// Eject all players on the same tile
// as the player in the direction they are facing
void cmd_eject(server_t *srv, connection_t *cl, regex_parse_t *parse)
{
    player_t *player = get_player_by_fd(cl, srv);
    player_t *tmp = srv->game->players;

    while (tmp != NULL) {
        if (tmp->square == player->square && tmp != player) {
            eject_player(tmp);
        }
        tmp = tmp->next;
    }
    player->square->eggs = NULL;
    queue_formatted_message(cl, "ok");
}
