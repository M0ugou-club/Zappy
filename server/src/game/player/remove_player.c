/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** remove_player
*/

#include <stdbool.h>
#include "game.h"

void remove_player(player_t **player, player_t *to_remove)
{
    player_t *tmp = *player;
    player_t *prev = NULL;

    if (tmp != NULL && tmp == to_remove) {
        *player = tmp->next;
        free(tmp);
        return;
    }
    while (tmp != NULL && tmp != to_remove) {
        prev = tmp;
        tmp = tmp->next;
    }
    if (tmp == NULL)
        return;
    prev->next = tmp->next;
    free(tmp);
}