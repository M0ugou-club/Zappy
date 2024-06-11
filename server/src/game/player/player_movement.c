/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** player_movement
*/

#include "game.h"

void move_player(player_t *player, direction_t direction)
{
    switch (direction) {
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
}

void turn_player(player_t *player, direction_t direction)
{
    player->direction = direction;
}
