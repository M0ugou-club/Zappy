/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** move
*/

#include "server.h"

// Move the player forward
void cmd_forward(server_t *srv, connection_t *cl, regex_parse_t *parse)
{
    player_t *player = get_player_by_fd(srv->game->players, cl->fd);

    switch (player->direction) {
        case NORTH:
            player->square = player->square->north;
            break;
        case SOUTH:
            player->square = player->square->south;
            break;
        case EAST:
            player->square = player->square->east;
            break;
        case WEST:
            player->square = player->square->west;
            break;
    }
    queue_formatted_message(cl, "ok\n");
    broadcast_gui(srv, "ppo %d %d %d %d\n", player->id,
        player->square->pos_x, player->square->pos_y, player->direction);
}

// Turn the player to the right
void cmd_right(server_t *srv, connection_t *cl, regex_parse_t *parse)
{
    player_t *player = get_player_by_fd(srv->game->players, cl->fd);

    player->direction = (player->direction + 1) % 4 + 1;
    queue_formatted_message(cl, "ok\n");
    broadcast_gui(srv, "ppo %d %d %d %d\n", player->id,
        player->square->pos_x, player->square->pos_y, player->direction);
}

// Turn the player to the left
void cmd_left(server_t *srv, connection_t *cl, regex_parse_t *parse)
{
    player_t *player = get_player_by_fd(srv->game->players, cl->fd);

    player->direction = (player->direction + 3) % 4 + 1;
    queue_formatted_message(cl, "ok\n");
    broadcast_gui(srv, "ppo %d %d %d %d\n", player->id,
        player->square->pos_x, player->square->pos_y, player->direction);
}
