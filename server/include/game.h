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
    char **eggs;
    int items[NONE];
    struct square_s *north;
    struct square_s *south;
    struct square_s *east;
    struct square_s *west;
} square_t;

typedef struct player_s {
    size_t id;
    char *team;
    square_t *square;
    direction_t direction;
    size_t level;
    unsigned int inventory[NONE];
    int fd;
    struct player_s *next;
} player_t;

typedef struct game_s {
    int map_x;
    int map_y;
    max_items_t *max_items;
    square_t **map;
    player_t *players;
    int max_players;
    char **teams;
    int *team_slots;
} game_t;

game_t *init_game(int x, int y, char **teams);
void free_game(game_t *game);
max_items_t *fill_density(int x, int y);

#endif /* !GAME_H_ */
