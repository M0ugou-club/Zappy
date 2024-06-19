/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** egg
*/

#include "server.h"

static int count_str_array(char **arr)
{
    int i = 0;

    while (arr[i] != NULL)
        i++;
    return i;
}

static bool check_egg_in_eggs(square_t *square, char *team_name)
{
    if (square->eggs == NULL) {
        square->eggs = malloc(sizeof(egg_t *) * 2);
        square->eggs[0] = malloc(sizeof(egg_t));
        square->eggs[0]->id = 0;
        square->eggs[0]->team = team_name;
        square->eggs[1] = malloc(sizeof(egg_t));
        square->eggs[1]->id = -1;
        square->eggs[1]->team = NULL;
        return true;
    }
    return false;
}

void add_egg(square_t *square, char *team_name)
{
    size_t id = 1;
    int nb_eggs = 0;

    if (check_egg_in_eggs(square, team_name) == true)
        return;
    for (nb_eggs = 0; square->eggs[nb_eggs]->id != -1; nb_eggs++);
    square->eggs = realloc(square->eggs, sizeof(egg_t *) * (nb_eggs + 2));
    square->eggs[nb_eggs] = malloc(sizeof(egg_t));
    square->eggs[nb_eggs]->id = id;
    square->eggs[nb_eggs]->team = team_name;
    square->eggs[nb_eggs + 1] = malloc(sizeof(egg_t));
    square->eggs[nb_eggs + 1]->id = -1;
    square->eggs[nb_eggs + 1]->team = NULL;
    id++;
}

void del_egg(square_t *square, char *team_name)
{
    int i = 0;
    int nb_eggs = 0;

    if (square->eggs == NULL)
        return;
    for (i = 0; square->eggs[i]->id == -1; i++) {
        if (strcmp(square->eggs[i]->team, team_name) == 0) {
            free(square->eggs[i]->team);
            square->eggs[i]->team = NULL;
            square->eggs[i]->id = -1;
            break;
        }
    }
    for (nb_eggs = 0; square->eggs[nb_eggs]->id != -1; nb_eggs++);
    for (int j = i; square->eggs[j]->id != -1; j++) {
        square->eggs[j] = square->eggs[j + 1];
    }
    square->eggs = realloc(square->eggs, sizeof(egg_t *) * (nb_eggs));
}

bool check_egg(square_t *square, char *team_name)
{
    if (square->eggs == NULL)
        return false;
    for (int i = 0; square->eggs[i]->id == -1; i++) {
        if (strcmp(square->eggs[i]->team, team_name) == 0)
            return true;
    }
    return false;
}

bool check_eggs(game_t *game, char *team_name)
{
    bool res = false;
    bool tmp = false;

    for (int x = 0; x < game->map_x; x++) {
        for (int y = 0; y < game->map_y; y++) {
            tmp = check_egg(&game->map[x][y], team_name);
            tmp == true ? res = true : 0;
        }
    }
    return res;
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
