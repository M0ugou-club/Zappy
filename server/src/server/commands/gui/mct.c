/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** mct
*/

#include "server.h"

void mct(server_t *srv, connection_t *cl)
{
    for (int y = 0; y < srv->game->map_y; y++) {
        for (int x = 0; x < srv->game->map_x; x++) {
            bct(srv, cl, x, y);
        }
    }
}

// Send the contents of all the tiles
void cmd_mct(server_t *srv, connection_t *cl, regex_parse_t *parse)
{
    mct(srv, cl);
}
