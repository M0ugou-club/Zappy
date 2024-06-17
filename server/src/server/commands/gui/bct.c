/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** bct
*/

#include "server.h"

void bct(server_t *srv, connection_t *cl, int x, int y)
{
    square_t *square = &srv->game->map[y][x];

    queue_formatted_message(cl, "bct %d %d %d %d %d %d %d %d %d\n", x, y,
        square->items[0], square->items[1], square->items[2],
        square->items[3], square->items[4], square->items[5], square->items[6]);
}

// Send the contents of a tile
void cmd_bct(server_t *srv, connection_t *cl, regex_parse_t *parse)
{
    int x = atoi(parse->pmatch[1].rm_so);
    int y = atoi(parse->pmatch[2].rm_so);

    bct(srv, cl, x, y);
}
