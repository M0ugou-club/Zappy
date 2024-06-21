/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** sgt
*/

#include "server.h"

void sgt(server_t *srv, connection_t *cl)
{
    queue_formatted_message(cl, "sgt %zu\n", srv->args->frequency);
}

// Send the time unit
void cmd_sgt(server_t *srv, connection_t *cl, regex_parse_t *parse)
{
    sgt(srv, cl);
}
