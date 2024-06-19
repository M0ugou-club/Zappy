/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** spawn_player
*/

#include "server.h"

static bool is_egg(game_t *game, int x, int y, player_t *n_player)
{
    for (int i = 0; game->map[x][y].eggs[i]->id != -1; i++) {
        if (strcmp(game->map[x][y].eggs[i]->team, n_player->team) == 0) {
            n_player->square = &game->map[x][y];
            del_egg(&game->map[x][y], n_player->team);
            return true;
        }
    }
    return false;
}

static bool loop_in_map(game_t *game, player_t *n_player)
{
    bool found = false;

    for (int x = 0; x < game->map_x && !found; x++) {
        for (int y = 0; y < game->map_y && !found; y++) {
            found = is_egg(game, x, y, n_player);
        }
    }
    return found;
}

void spawn_player(game_t *game, char *team, int fd)
{
    player_t *n_player = new_player(team);
    bool found = false;

    n_player->fd = fd;
    while(!found) {
        found = loop_in_map(game, n_player);
    }
    game->players = add_player(game->players, n_player);
}
