/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** tna
*/

#include "server.h"

// Send the team names
void cmd_tna(server_t *srv, connection_t *cl, regex_parse_t *parse)
{
    for (int i = 0; srv->game->teams[i]; i++) {
        queue_formatted_message(cl, "tna %s\n", srv->game->teams[i]);
    }
}
