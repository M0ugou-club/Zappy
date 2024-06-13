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
    player_t *player = get_player_by_fd(cl, srv);

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
    queue_formatted_message(cl, "ok");
}

// Turn the player to the right
void cmd_right(server_t *srv, connection_t *cl, regex_parse_t *parse)
{
    player_t *player = get_player_by_fd(cl, srv);

    switch (player->direction) {
        case NORTH:
            player->direction = EAST;
            break;
        case SOUTH:
            player->direction = WEST;
            break;
        case EAST:
            player->direction = SOUTH;
            break;
        case WEST:
            player->direction = NORTH;
            break;
    }
    queue_formatted_message(cl, "ok");
}

// Turn the player to the left
void cmd_left(server_t *srv, connection_t *cl, regex_parse_t *parse)
{
    player_t *player = get_player_by_fd(cl, srv);

    switch (player->direction) {
        case NORTH:
            player->direction = WEST;
            break;
        case SOUTH:
            player->direction = EAST;
            break;
        case EAST:
            player->direction = NORTH;
            break;
        case WEST:
            player->direction = SOUTH;
            break;
    }
    queue_formatted_message(cl, "ok");
}
