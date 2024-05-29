/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** free_game
*/

#include "game.h"

void free_game(game_t *game)
{
    free(game->map);
    free(game->players);
    free(game);
}
