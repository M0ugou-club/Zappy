/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** tna
*/

#include "server.h"

void tna(server_t *srv, connection_t *cl)
{
    for (int i = 0; srv->args->teams[i]; i++) {
        queue_formatted_message(cl, "tna %s\n", srv->args->teams[i]);
    }
}

// Send the team names
void cmd_tna(server_t *srv, connection_t *cl, regex_parse_t *parse)
{
    tna(srv, cl);
}
