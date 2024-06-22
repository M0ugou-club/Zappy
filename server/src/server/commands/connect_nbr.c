/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** connect_nbr
*/

#include "server.h"

size_t count_eggs_square(square_t *sq, char *team)
{
    size_t count = 0;

    if (sq->eggs == NULL)
        return count;
    for (int i = 0; sq->eggs[i]; i++) {
        if (strcmp(sq->eggs[i]->team, team) == 0)
            count++;
    }
    return count;
}

size_t count_eggs(server_t *srv, char *team)
{
    square_t **map = srv->game->map;
    size_t count = 0;

    for (int xdx = 0; xdx < srv->game->map_x; xdx++) {
        for (int ydx = 0; ydx < srv->game->map_y; ydx++) {
            count += count_eggs_square(&map[xdx][ydx], team);
        }
    }
    return count;
}

// Get the amount of free slots in the team
void cmd_connect_nbr(server_t *srv, connection_t *cl, regex_parse_t *parse)
{
    size_t count = count_eggs(srv, cl->team);

    queue_formatted_message(cl, "%ld\n", count);
}
