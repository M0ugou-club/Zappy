/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** player
*/

#ifndef PLAYER_H_
    #define PLAYER_H_

    #include "game.h"

player_t *init_players(int max_players);
player_t *add_player(player_t *players, int id, char *team);
player_t pop_player(player_t *players, int id);
player_t *get_player_by_id(player_t *players, int id);
int get_player_count(player_t *players);

#endif /* !PLAYER_H_ */

