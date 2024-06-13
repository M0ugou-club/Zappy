/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** egg
*/

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "server.h"
#include "game.h"

static int count_str_array(char **arr)
{
    int i = 0;

    while (arr[i] != NULL)
        i++;
    return i;
}

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

void del_egg(square_t *square, char *team_name)
{
    int str_array_len = 0;

    if (square->eggs == NULL)
        return;
    str_array_len = count_str_array(square->eggs);
    for (int i = 0; i < str_array_len; i++) {
        if (strcmp(square->eggs[i], team_name) == 0) {
            free(square->eggs[i]);
            square->eggs[i] = NULL;
            break;
        }
    }
    for (int i = 0; i < str_array_len; i++) {
        if (square->eggs[i] == NULL) {
            free(square->eggs[i]);
            square->eggs[i] = strdup(square->eggs[i + 1]);
            free(square->eggs[i + 1]);
            square->eggs[i + 1] = NULL;
        }
    }
}

bool check_egg(square_t *square, char *team_name)
{
    int str_array_len = 0;

    if (square->eggs == NULL)
        return false;
    str_array_len = count_str_array(square->eggs);
    for (int i = 0; i < str_array_len; i++) {
        if (strcmp(square->eggs[i], team_name) == 0)
            return true;
    }
    return false;
}

void place_eggs(game_t *game, args_t *args)
{
    int x;
    int y;
    int nb_teams = 0;
    int count = 0;

    nb_teams = get_array_size(args->teams);
    while (count < nb_teams * args->maxClients) {
        for (int i = 0; i < nb_teams; i++) {
            x = rand() % game->map_x;
            y = rand() % game->map_y;
            add_egg(&game->map[x][y], args->teams[i]);
            count++;
        }
    }
}
