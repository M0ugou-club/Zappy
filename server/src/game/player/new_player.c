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

    if (player == NULL)
        return NULL;
    player->id = rand() % 2147483646;
    player->team = team_name;
    player->level = 1;
    player->fd = 0;
    player->direction = rand() % 4;
    player->square = NULL;
    player->inventory[NONE];
    player->next = NULL;
    return player;
}
