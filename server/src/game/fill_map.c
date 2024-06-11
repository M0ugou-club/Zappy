/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** fill_map
*/

#include <time.h>
#include "game.h"
#include "egg.h"

static const float density[7] = {0.5, 0.3, 0.15, 0.1, 0.1, 0.08, 0.05};

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

void place_items_randomly(game_t *game, args_t *args)
{
    int x;
    int y;
    int count;

    for (int i = 0; i < 7; i++) {
        count = 0;
        while (count < game->max_items->food) {
            x = rand() % game->map_x;
            y = rand() % game->map_y;
            if (game->map[x][y].items[i] == 0) {
                game->map[x][y].items[i] += 1;
                count++;
            }
        }
    }
    place_eggs(game, args);
}
