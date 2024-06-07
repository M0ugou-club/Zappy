/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** egg
*/

#include "game.h"

void add_egg(square_t *square, char *team_name)
{
    int str_array_len = 0;

    if (square->eggs == NULL) {
        square->eggs = malloc(sizeof(char *) * 2);
        square->eggs[0] = strdup(team_name);
        square->eggs[1] = NULL;
        return;
    }
    str_array_len = count_str_array(square->eggs);
    square->eggs = realloc(square->eggs, sizeof(char *) * (str_array_len + 2));
    square->eggs[str_array_len] = strdup(team_name);
    square->eggs[str_array_len + 1] = NULL;
}
