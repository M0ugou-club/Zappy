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
    player->id++;
    player->team = team_name;
    player->level = 1;
    player->fd = 0;
    player->direction = rand() % 4;
    player->square = NULL;
    player->next = NULL;
    player->disconnect = false;
    player->incantation = false;
    memset(player->inventory, 0, 7);
    player->inventory[FOOD] = 10;
    player->last_action = 0;
    player->last_eat = 0;
    return player;
}
