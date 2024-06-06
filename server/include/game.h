/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** game
*/

#ifndef GAME_H_
    #define GAME_H_

    #include <stdlib.h>

typedef enum direction_e {
    NORTH,
    SOUTH,
    EAST,
    WEST
} direction_t;

typedef enum item_e {
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME,
    FOOD,
    NONE
} item_t;

typedef struct max_items_s {
    int food;
    int linemate;
    int deraumere;
    int sibur;
    int mendiane;
    int phiras;
    int thystame;
} max_items_t;

typedef struct square_s {
    int food;
    int linemate;
    int deraumere;
    int sibur;
    int mendiane;
    int phiras;
    int thystame;
} square_t;

typedef struct player_s {
    size_t id;
    char *team;
    struct square_s *square;
    direction_t direction;
    size_t level;
    item_t inventory[NONE];
} player_t;

typedef struct game_s {
    int map_x;
    int map_y;
    struct max_items_s *max_items;
    struct square_s **map;
    struct player_s *players;
    int max_players;
    char **teams;
    int *team_slots;
} game_t;

game_t *init_game(int x, int y, char **teams);
void free_game(game_t *game);
max_items_t *fill_density(int x, int y);
void place_items_randomly(game_t *game);

#endif /* !GAME_H_ */
