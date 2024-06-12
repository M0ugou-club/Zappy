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

    if (player->direction == NORTH) {
        player->square = player->square->north;
    } else if (player->direction == SOUTH) {
        player->square = player->square->south;
    } else if (player->direction == EAST) {
        player->square = player->square->east;
    } else if (player->direction == WEST) {
        player->square = player->square->west;
    }
    queue_formatted_message(cl, "ok");
}

// Turn the player to the right
void cmd_right(server_t *srv, connection_t *cl, regex_parse_t *parse)
{
    player_t *player = get_player_by_fd(cl, srv);

    if (player->direction == NORTH) {
        player->direction = EAST;
    } else if (player->direction == SOUTH) {
        player->direction = WEST;
    } else if (player->direction == EAST) {
        player->direction = SOUTH;
    } else if (player->direction == WEST) {
        player->direction = NORTH;
    }
    queue_formatted_message(cl, "ok");
}

// Turn the player to the left
void cmd_left(server_t *srv, connection_t *cl, regex_parse_t *parse)
{
    player_t *player = get_player_by_fd(cl, srv);

    if (player->direction == NORTH) {
        player->direction = WEST;
    } else if (player->direction == SOUTH) {
        player->direction = EAST;
    } else if (player->direction == EAST) {
        player->direction = NORTH;
    } else if (player->direction == WEST) {
        player->direction = SOUTH;
    }
    queue_formatted_message(cl, "ok");
}
