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
    game->map = malloc(sizeof(square_t *) * x + 1);
    for (int i = 0; i < x; i++) {
        game->map[i] = malloc(sizeof(square_t) * y + 1);
    }
    game->players = NULL;
    return game;
}
