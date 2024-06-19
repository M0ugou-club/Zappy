/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** eject
*/

#include "server.h"

static void eject_player(player_t *player)
{
    switch (player->direction) {
        case NORTH:
            player->square = player->square->south;
            break;
        case SOUTH:
            player->square = player->square->north;
            break;
        case EAST:
            player->square = player->square->west;
            break;
        case WEST:
            player->square = player->square->east;
            break;
    }
}

// Eject all players on the same tile
// as the player in the direction they are facing
void cmd_eject(server_t *srv, connection_t *cl, regex_parse_t *parse)
{
    player_t *player = get_player_by_fd(srv->game->players, cl->fd);
    player_t *tmp = srv->game->players;
    int check = 0;

    while (tmp != NULL) {
        if (tmp->square == player->square && tmp != player) {
            eject_player(tmp);
            check = 1;
        }
        tmp = tmp->next;
    }
    if (check == 0) {
        queue_formatted_message(cl, "ko\n");
        return;
    }
    player->square->eggs = NULL;
    queue_formatted_message(cl, "ok\n");
}
