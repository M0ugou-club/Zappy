/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** egg
*/

#ifndef EGG_H_
    #define EGG_H_

    #include "server.h"

void add_egg(square_t *square, char *team_name);
void del_egg(square_t *square, char *team_name);
bool check_egg(square_t *square, char *team_name);
void place_eggs(game_t *game, args_t *args);

#endif /* !EGG_H_ */
