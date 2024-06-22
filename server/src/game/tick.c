/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** tick
*/

#include "game.h"
#include "server.h"

static bool eat(server_t *srv, player_t *ply)
{
    connection_t *tmp = get_client_by_fd(srv->cons, ply->fd);

    if (tmp == NULL)
        return false;
    if (time_passed(&ply->eat_cooldown)) {
        if (ply->inventory[FOOD] > 0) {
            ply->inventory[FOOD] -= 1;
            set_cooldown(&ply->eat_cooldown, EAT_TIME / srv->args->frequency);
            return true;
        } else {
            send_formatted_message(tmp, "dead\n");
            return false;
        }
    }
    return true;
}

static void apply_incantation(server_t *srv, player_t *ply)
{
    connection_t *cl = get_client_by_fd(srv->cons, ply->fd);

    if (ply->incantation && time_passed(&ply->action_cooldown)) {
        printf("Player %ld has leveled up (%ld -> %ld)\n",
            ply->id, ply->level, ply->level + 1);
        ply->incantation = false;
        incantation_message(srv, cl, ply);
    }
}

static void refill(server_t *srv)
{
    if (!time_passed(&srv->game->refill_cooldown))
        return;
    refill_map(srv);
    set_cooldown(&srv->game->refill_cooldown,
        REFILL_TIME / srv->args->frequency);
}

static size_t get_winning_players(server_t *srv, char *team)
{
    size_t count = 0;

    for (player_t *ply = srv->game->players; ply != NULL; ply = ply->next)
        if (strcmp(ply->team, team) == 0 && ply->level == 8)
            count++;
    return count;
}

static void check_win(server_t *srv)
{
    for (int i = 0; srv->args->teams[i]; i++) {
        if (get_winning_players(srv, srv->args->teams[i]) >= 6) {
            printf("Team %s has won the game\n", srv->args->teams[i]);
            broadcast_gui(srv, "seg %s\n", srv->args->teams[i]);
            srv->close = true;
            return;
        }
    }
}

void game_tick(server_t *srv)
{
    player_t *ply = srv->game->players;

    while (ply != NULL) {
        ply->disconnect = !eat(srv, ply);
        if (!ply->disconnect)
            apply_incantation(srv, ply);
        ply = ply->next;
    }
    refill(srv);
    check_win(srv);
}
