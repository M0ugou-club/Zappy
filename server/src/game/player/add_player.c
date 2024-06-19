/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** add_player
*/

#include "game.h"

player_t *add_player(player_t *player, player_t *new_player)
{
    player_t *tmp = player;

    if (player == NULL)
        return new_player;
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = new_player;
    return player;
}
