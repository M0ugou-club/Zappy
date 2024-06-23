/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** free_game
*/

#include "game.h"

static void free_eggs(square_t *square)
{
    int idx = 0;

    if (!square->eggs)
        return;
    while (square->eggs[idx]->id != -1) {
        free(square->eggs[idx]);
        idx++;
    }
    free(square->eggs[idx]);
    free(square->eggs);
}

void free_game(game_t *game)
{
    for (int i = 0; i < game->map_x; i++) {
        for (int j = 0; j < game->map_y; j++)
            free_eggs(&game->map[i][j]);
        free(game->map[i]);
    }
    free(game->map);
    free(game->max_items);
    free(game->players);
    free(game);
}
