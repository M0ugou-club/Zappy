/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** get_player_by_fd
*/

#include "server.h"
#include "game.h"

player_t *get_player_by_fd(player_t *players, int fd)
{
    player_t *tmp = players;

    while (tmp != NULL) {
        if (tmp->fd == fd)
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}
