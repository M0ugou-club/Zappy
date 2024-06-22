/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** fill_map
*/

#include <time.h>
#include "server.h"

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
        game->map[x][y].items[i] += 1;
        count++;
    }
}

static int count_items(game_t *game, int i)
{
    int count = 0;

    for (int x = 0; x < game->map_x; x++) {
        for (int y = 0; y < game->map_y; y++) {
            count += game->map[x][y].items[i];
        }
    }
    return count;
}

static void broadcast_updated_cells(server_t *srv)
{
    for (int x = 0; x < srv->game->map_x; x++) {
        for (int y = 0; y < srv->game->map_y; y++) {
            if (srv->game->map[x][y].updated == true) {
                broadcast_gui(srv, "bct %d %d %d %d %d %d %d %d %d\n", x, y,
                srv->game->map[x][y].items[0], srv->game->map[x][y].items[1],
                srv->game->map[x][y].items[2], srv->game->map[x][y].items[3],
                srv->game->map[x][y].items[4], srv->game->map[x][y].items[5],
                srv->game->map[x][y].items[6]);
                srv->game->map[x][y].updated = false;
            }
        }
    }

}

void refill_map(server_t *srv)
{
    int x;
    int y;
    int count = 0;
    int nb_items = 0;

    for (int i = 0; i < NONE; i++) {
        count = 0;
        nb_items = count_items(srv->game, i);
        while (count < srv->game->max_items->items[i] - nb_items) {
            x = rand() % srv->game->map_x;
            y = rand() % srv->game->map_y;
            srv->game->map[x][y].items[i] += 1;
            srv->game->map[x][y].updated = true;
            count++;
        }
    }
    broadcast_updated_cells(srv);
}

void place_items_randomly(game_t *game, args_t *args)
{
    for (int i = 0; i < 7; i++) {
        add_items(game, i);
    }
    place_eggs(game, args);
}
