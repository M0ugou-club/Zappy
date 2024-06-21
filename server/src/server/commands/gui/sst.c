/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** sst
*/

#include "server.h"

void sst(server_t *srv, connection_t *cl, int time_unit)
{
    srv->args->frequency = time_unit;
    queue_formatted_message(cl, "sst %d\n", srv->args->frequency);
}

// Time unit modification
void cmd_sst(server_t *srv, connection_t *cl, regex_parse_t *parse)
{
    char *time_unit_str = NULL;
    int time_unit = 0;

    time_unit_str = strndup(parse->str + parse->pmatch[1].rm_so,
        parse->pmatch[1].rm_eo - parse->pmatch[1].rm_so);
    time_unit = atoi(time_unit_str);
    sst(srv, cl, time_unit);
    free(time_unit_str);
}
