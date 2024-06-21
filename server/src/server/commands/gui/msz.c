/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** msz
*/

#include "server.h"

void msz(server_t *srv, connection_t *cl)
{
    queue_formatted_message(cl, "msz %d %d\n", srv->game->map_x,
        srv->game->map_y);
}

// Send the size of the map
void cmd_msz(server_t *srv, connection_t *cl, regex_parse_t *parse)
{
    msz(srv, cl);
}
