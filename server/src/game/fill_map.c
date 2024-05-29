/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** fill_map
*/

#include "game.h"

static const int density[7] = {0.5, 0.3, 0.15, 0.1, 0.1, 0.08, 0.05};


//ressource quantity = map_x * map_y * density
//if 10x10 map, 50 food, 30 linemate, 15 deraumere, 10 sibur, 10 mendiane, 8 phiras, 5 thystame

max_items_t *fill_density(int x, int y)
{
    max_items_t *max_items = malloc(sizeof(max_items_t));

    max_items->food = x * y * 0.5;
    max_items->linemate = x * y * 0.3;
    max_items->deraumere = x * y * 0.15;
    max_items->sibur = x * y * 0.1;
    max_items->mendiane = x * y * 0.1;
    max_items->phiras = x * y * 0.08;
    max_items->thystame = x * y * 0.05;
    return max_items;
}

void fill_map(game_t *game)
{
    for (int i = 0; i < game->map_x; i++) {
        for (int j = 0; j < game->map_y; j++) {
            
        }
    }
}
