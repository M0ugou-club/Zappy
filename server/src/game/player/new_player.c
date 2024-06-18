/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** new_player
*/

#include "game.h"

player_t *new_player(char *team_name)
{
    player_t *player = malloc(sizeof(player_t));
    static int id = 0;

    if (player == NULL)
        return NULL;
    player->id = id++;
    player->team = team_name;
    player->level = 1;
    player->fd = 0;
    player->direction = rand() % 4;
    player->square = NULL;
    player->next = NULL;
    player->disconnect = false;
    return player;
}
