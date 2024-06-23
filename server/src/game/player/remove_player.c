/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** remove_player
*/

#include <stdbool.h>
#include "game.h"

static bool remove_first(player_t **players, int sockfd, player_t *ply)
{
    if (ply != NULL && ply->fd == sockfd) {
        *players = ply->next;
        free(ply);
        return true;
    }
    return false;
}

void remove_player(player_t **players, int sockfd)
{
    player_t *tmp = *players;
    player_t *prev = NULL;

    if (remove_first(players, sockfd, tmp))
        return;
    while (tmp != NULL && tmp->fd != sockfd) {
        prev = tmp;
        tmp = tmp->next;
    }
    if (tmp == NULL)
        return;
    prev->next = tmp->next;
    free(tmp);
}
