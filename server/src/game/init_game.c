/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** init_game
*/

#include <string.h>
#include <stdlib.h>
#include "game.h"

game_t *init_game(int x, int y, char **teams)
{
    game_t *game = malloc(sizeof(game_t));

    game->map_x = x;
    game->map_y = y;
    game->teams = teams;
    game->max_items = fill_density(x, y);
    game->map = malloc(sizeof(square_t) * x * y);
    for (int xdx = 0; xdx < x; xdx++) {
        game->map[xdx] = malloc(sizeof(square_t) * y);
        for (int ydy = 0; ydy < y; ydy++) {
            game->map[xdx][ydy].eggs = NULL;
            game->map[xdx][ydy].north = game->map[xdx + (ydy - 1) * x];
            game->map[xdx][ydy].south = game->map[xdx + (ydy + 1) * x];
            game->map[xdx][ydy].east = game->map[xdx + 1 + ydy * x];
            game->map[xdx][ydy].west = game->map[xdx - 1 + ydy * x];
        }
    }
    game->players = NULL;
    return game;
}
