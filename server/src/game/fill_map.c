/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** fill_map
*/

#include <time.h>
#include "game.h"

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

static void place_food(game_t *game)
{
    int x;
    int y;
    int count;

    srand(time(NULL));
    for (count = 0; count < game->max_items->food; count++) {
        x = rand() % game->map_x;
        y = rand() % game->map_y;
        game->map[x][y].food++;
    }
}

static void place_linemate(game_t *game)
{
    int x;
    int y;
    int count;

    srand(time(NULL));
    for (count = 0; count < game->max_items->linemate; count++) {
        x = rand() % game->map_x;
        y = rand() % game->map_y;
        game->map[x][y].linemate++;
    }
}

static void place_deraumere(game_t *game)
{
    int x;
    int y;
    int count;

    srand(time(NULL));
    for (count = 0; count < game->max_items->deraumere; count++) {
        x = rand() % game->map_x;
        y = rand() % game->map_y;
        game->map[x][y].deraumere++;
    }
}

static void place_sibur(game_t *game)
{
    int x;
    int y;
    int count;

    srand(time(NULL));
    for (count = 0; count < game->max_items->sibur; count++) {
        x = rand() % game->map_x;
        y = rand() % game->map_y;
        game->map[x][y].sibur++;
    }
}

static void place_mendiane(game_t *game)
{
    int x;
    int y;
    int count;

    srand(time(NULL));
    for (count = 0; count < game->max_items->mendiane; count++) {
        x = rand() % game->map_x;
        y = rand() % game->map_y;
        game->map[x][y].mendiane++;
    }
}

static void place_phiras(game_t *game)
{
    int x;
    int y;
    int count;

    srand(time(NULL));
    for (count = 0; count < game->max_items->phiras; count++) {
        x = rand() % game->map_x;
        y = rand() % game->map_y;
        game->map[x][y].phiras++;
    }
}

static void place_thystame(game_t *game)
{
    int x;
    int y;
    int count;

    srand(time(NULL));
    for (count = 0; count < game->max_items->thystame; count++) {
        x = rand() % game->map_x;
        y = rand() % game->map_y;
        game->map[x][y].thystame++;
    }
}

void place_items_randomly(game_t *game)
{
    place_food(game);
    place_linemate(game);
    place_deraumere(game);
    place_sibur(game);
    place_mendiane(game);
    place_phiras(game);
    place_thystame(game);
}
