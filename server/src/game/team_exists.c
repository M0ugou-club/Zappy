/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** team_exists
*/

#include "game.h"

bool team_exists(char **teams, char *team)
{
    for (int i = 0; teams[i]; i++) {
        if (strcmp(teams[i], team) == 0)
            return true;
    }
    return false;
}
