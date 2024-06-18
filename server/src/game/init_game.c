/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** init_game
*/

#include "server.h"

// link map borders so it loops on itself
static void link_map(game_t *game, const int map_x, const int map_y)
{
    for (int x = 0; x < map_x; x++) {
        game->map[x][0].north = &game->map[x][map_y - 1];
        game->map[x][map_y - 1].south = &game->map[x][0];
    }
    for (int y = 0; y < map_y; y++) {
        game->map[0][y].west = &game->map[map_x - 1][y];
        game->map[map_x - 1][y].east = &game->map[0][y];
    }
}

static void init_map(game_t *game, const int x, const int y)
{
    game->map = malloc(sizeof(square_t) * x * y);
    for (int xdx = 0; xdx < x; xdx++) {
        game->map[xdx] = malloc(sizeof(square_t) * y);
        for (int ydy = 0; ydy < y; ydy++) {
            game->map[xdx][ydy].eggs = NULL;
            game->map[xdx][ydy].pos_x = xdx;
            game->map[xdx][ydy].pos_y = ydy;
            game->map[xdx][ydy].north = game->map[xdx + (ydy - 1) * x];
            game->map[xdx][ydy].south = game->map[xdx + (ydy + 1) * x];
            game->map[xdx][ydy].east = game->map[xdx + 1 + ydy * x];
            game->map[xdx][ydy].west = game->map[xdx - 1 + ydy * x];
        }
    }
    link_map(game, x, y);
}

game_t *init_game(int x, int y, char **teams, args_t *args)
{
    game_t *game = malloc(sizeof(game_t));

    game->map_x = x;
    game->map_y = y;
    game->teams = teams;
    game->max_items = fill_density(x, y);
    game->players = NULL;
    init_map(game, x, y);
    place_items_randomly(game, args);
    return game;
}
