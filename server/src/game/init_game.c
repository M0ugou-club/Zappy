/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** init_game
*/

#include "game.h"

game_t *init_game(int x, int y, char **teams)
{
    game_t *game = malloc(sizeof(game_t));

    game->teams = teams;
    game->map = malloc(sizeof(square_t) * x * y);
    for (int xdx = 0; xdx < x; xdx++) {
        for (int ydy = 0; ydy < y; ydy++) {
            game->map[xdx + ydy * x].north = &game->map[xdx + (ydy - 1) * x];
            game->map[xdx + ydy * x].south = &game->map[xdx + (ydy + 1) * x];
            game->map[xdx + ydy * x].east = &game->map[xdx + 1 + ydy * x];
            game->map[xdx + ydy * x].west = &game->map[xdx - 1 + ydy * x];
        }
    }
    game->players = NULL;
    return game;
}
