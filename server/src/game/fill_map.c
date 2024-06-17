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

    if (max_items == NULL)
        return NULL;
    for (int i = 0; i < 7; i++) {
        max_items->items[i] = density[i] * x * y;
    }
    return max_items;
}

static void add_items(game_t *game, int i)
{
    int x;
    int y;
    int count = 0;

    while (count < game->max_items->items[i]) {
        x = rand() % game->map_x;
        y = rand() % game->map_y;
        if (game->map[x][y].items[i] == 0) {
            game->map[x][y].items[i] += 1;
            count++;
        }
    }
}

void place_items_randomly(game_t *game, args_t *args)
{
    for (int i = 0; i < 7; i++) {
        add_items(game, i);
    }
    place_eggs(game, args);
}
