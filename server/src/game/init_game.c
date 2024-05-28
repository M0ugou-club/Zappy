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
    game->map = malloc(sizeof(square_t) * x * y);
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            memset(game->map[i][j].items, 0, sizeof(item_t) * NONE);
        }
    }
    game->players = NULL;
    return game;
}
