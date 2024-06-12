/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** eject
*/

#include "server.h"

// Eject all players on the same tile
// as the player in the direction they are facing
void cmd_eject(server_t *srv, connection_t *cl, regex_parse_t *parse)
{
    player_t *player = get_player_by_fd(cl, srv);
    player_t *tmp = srv->game->players;

    while (tmp != NULL) {
        if (tmp->square == player->square && tmp != player) {
            if (tmp->direction == NORTH) {
                tmp->square = tmp->square->south;
            } else if (tmp->direction == SOUTH) {
                tmp->square = tmp->square->north;
            } else if (tmp->direction == EAST) {
                tmp->square = tmp->square->west;
            } else if (tmp->direction == WEST) {
                tmp->square = tmp->square->east;
            }
        }
        tmp = tmp->next;
    }
    player->square->eggs = NULL;
}
