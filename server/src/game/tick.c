/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** tick
*/

#include "server.h"

static bool eat(server_t *srv, player_t *ply)
{
    connection_t *tmp = get_client_by_fd(srv->cons, ply->fd);

    if (difftime(time(NULL), ply->last_eat)
        >= EAT_TIME / srv->args->frequency) {
        if (ply->inventory[FOOD] > 0) {
            ply->inventory[FOOD] -= 1;
            ply->last_eat = time(NULL);
            return true;
        } else {
            queue_message(tmp, "dead\n");
            return false;
        }
    }
    return true;
}

void game_tick(server_t *srv)
{
    player_t *ply = srv->game->players;

    srv->game->tick++;
    while (ply != NULL) {
        ply->disconnect = !eat(srv, ply);
        ply = ply->next;
    }
}
