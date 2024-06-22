/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** init_game
*/

#include "server.h"

static void link_cell(game_t *game, const int xdx, const int ydx)
{
    if (xdx != 0)
        game->map[xdx][ydx].west = &game->map[xdx - 1][ydx];
    if (xdx != game->map_x - 1)
        game->map[xdx][ydx].east = &game->map[xdx + 1][ydx];
    if (ydx != 0)
        game->map[xdx][ydx].north = &game->map[xdx][ydx - 1];
    if (ydx != game->map_y - 1)
        game->map[xdx][ydx].south = &game->map[xdx][ydx + 1];
}

static void link_map(game_t *game, const int map_x, const int map_y)
{
    for (int xdx = 0; xdx < map_x; xdx++)
        for (int ydx = 0; ydx < map_y; ydx++)
            link_cell(game, xdx, ydx);
    for (int x = 0; x < map_x; x++) {
        game->map[x][0].north = &game->map[x][map_y - 1];
        game->map[x][map_y - 1].south = &game->map[x][0];
    }
    for (int y = 0; y < map_y; y++) {
        game->map[0][y].west = &game->map[map_x - 1][y];
        game->map[map_x - 1][y].east = &game->map[0][y];
    }
}

static void clear_items(game_t *game, const int x, const int y)
{
    for (int xdx = 0; xdx < x; xdx++) {
        for (int ydx = 0; ydx < y; ydx++) {
            memset(game->map[xdx][ydx].items, 0, sizeof(int) * 7);
        }
    }
}

static void init_map(game_t *game, const int x, const int y)
{
    game->map = malloc(sizeof(cell_t) * (x * y));
    for (int xdx = 0; xdx < x; xdx++) {
        game->map[xdx] = malloc(sizeof(cell_t) * y);
        for (int ydx = 0; ydx < y; ydx++) {
            game->map[xdx][ydx].eggs = NULL;
            game->map[xdx][ydx].pos_x = xdx;
            game->map[xdx][ydx].pos_y = ydx;
            game->map[xdx][ydx].updated = false;
        }
    }
    link_map(game, x, y);
    clear_items(game, x, y);
}

game_t *init_game(int x, int y, char **teams, args_t *args)
{
    game_t *game = malloc(sizeof(game_t));

    game->map_x = x;
    game->map_y = y;
    game->teams = teams;
    set_cooldown(&game->refill_cooldown, 0.0f);
    game->max_items = fill_density(x, y);
    game->players = NULL;
    init_map(game, x, y);
    place_items_randomly(game, args);
    return game;
}
