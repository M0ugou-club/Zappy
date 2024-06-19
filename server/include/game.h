/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** game
*/

#ifndef GAME_H_
    #define GAME_H_

    #include <stdlib.h>
    #include <time.h>
    #include <stdbool.h>
    #include <string.h>

    #define EAT_TIME 126.0f

typedef enum direction_e {
    NORTH = 1,
    SOUTH = 2,
    EAST = 3,
    WEST = 4
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
    int items[NONE];
} max_items_t;

typedef struct egg_s {
    char *team;
    size_t id;
} egg_t;

typedef struct square_s {
    egg_t **eggs;
    int items[NONE];
    int pos_x;
    int pos_y;
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
    time_t last_action;
    size_t level;
    unsigned int inventory[NONE];
    int fd;
    time_t last_eat;
    bool disconnect;
    bool incantation;
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
    time_t time_elapsed;
    ssize_t tick;
} game_t;

void add_egg(square_t *square, char *team_name);
void del_egg(square_t *square, char *team_name);
bool check_egg(square_t *square, char *team_name);
bool check_eggs(game_t *game, char *team_name);

void free_game(game_t *game);
max_items_t *fill_density(int x, int y);
bool team_exists(char **teams, char *team);

player_t *new_player(char *team_name);
player_t *add_player(player_t *player, player_t *new_player);
void remove_player(player_t **player, player_t *to_remove);

#endif /* !GAME_H_ */
