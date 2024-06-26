/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** server
*/

#ifndef SERVER_H_
    #define SERVER_H_

    #define EXIT_ERROR 84
    #define EXIT_SUCCESS 0

    #define BUFFER_SIZE 1024
    #define MAX_REGEX_MATCHES 16

    #define SEND(conn, msg) write(conn->fd, msg, strlen(msg))
    #define SEND_FD(fd, msg) write(fd, msg, strlen(msg))

    #define CMD_SUCCESS "ok\n"
    #define CMD_ERROR "ko\n"
    #define GRAPHIC_TEAM "GRAPHIC"

    #include <unistd.h>
    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>
    #include <regex.h>
    #include <stdarg.h>
    #include <sys/select.h>
    #include <sys/signal.h>
    #include <sys/socket.h>
    #include <sys/time.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include "socket.h"
    #include "connection.h"
    #include "game.h"

int get_array_size(char **arr);
bool time_passed(struct timeval *tv);
void set_cooldown(struct timeval *tv, float time);

typedef struct args_s {
    size_t port;
    size_t x;
    size_t y;
    char **teams;
    size_t maxClients;
    size_t frequency;
} args_t;

typedef struct arg_match_s {
    char *arg;
    int (*func)(args_t *args, char **argv, int *i, int argc);
} arg_match_t;

typedef struct main_args_s {
    int argc;
    char **argv;
} main_args_t;

int set_port(args_t *args, char **argv, int *i, int argc);
int set_x(args_t *args, char **argv, int *i, int argc);
int set_y(args_t *args, char **argv, int *i, int argc);
int set_max_clients(args_t *args, char **argv, int *i, int argc);
int set_frequency(args_t *args, char **argv, int *i, int argc);
int set_teams(args_t *args, char **argv, int *i, int argc);

args_t *get_args(int argc, char **argv);
void free_args(args_t *args);
bool error_args(args_t *args);

typedef struct server_s {
    struct args_s *args;
    sock_handle_t *sock;
    connection_t *cons;
    game_t *game;
    fd_set *readfds;
    fd_set *writefds;
    bool close;
} server_t;

typedef struct regex_parse_s {
    const char *str;
    regmatch_t pmatch[MAX_REGEX_MATCHES];
} regex_parse_t;

typedef struct command_regex_s {
    char *command;
    float time;
    void (*func)(server_t *srv, connection_t *cl, regex_parse_t *parse);
} command_regex_t;

char *append_buffer(char *dst, char src[BUFFER_SIZE],
    size_t *dst_len, size_t src_len);
char *slice_buffer(char **buffer, size_t *buffer_size, size_t bytes);
char *get_packet(char **buffer, size_t *buffer_size);

void build_sets(server_t *srv, connection_t *conn);
connection_t *get_client_by_fd(connection_t *cl, int sockfd);
void remove_connection(connection_t **cl, int sockfd);

void read_connections(server_t *srv);
void execute_connections(server_t *srv);
void disconnect_players(server_t *srv);
void execute_ai_commands(server_t *srv);
void player_enqueue(connection_t *cl, char *cmd);
char *player_dequeue(connection_t *cl);

void queue_message(connection_t *conn, char *msg);
void queue_formatted_message(connection_t *conn, const char *fmt, ...);
void send_formatted_message(connection_t *conn, const char *fmt, ...);
void send_message(server_t *srv, connection_t *cl);
void send_messages(server_t *srv);

server_t *init_server(args_t *args);
void free_server(server_t *server);
void close_server(const int signal, void *sr);
void run_server(server_t *server);

void place_eggs(game_t *game, args_t *args);
void place_items_randomly(game_t *game, args_t *args);

game_t *init_game(int x, int y, char **teams, args_t *args);
void refill_map(server_t *srv);
void game_tick(server_t *srv);

char *add_to_string(char *resp, char *li_cont);
void add_vals(int *cone_width, int *cone_gap, int *cone_distance);
int count_players_on_square(cell_t *square, server_t *srv);
cell_t *move_square_width(cell_t *square, direction_t orientation);

player_t *get_player_by_fd(player_t *players, int fd);
void clean_str(char *str);

/* Commands */
void cmd_forward(server_t *srv, connection_t *cl, regex_parse_t *parse);
void cmd_right(server_t *srv, connection_t *cl, regex_parse_t *parse);
void cmd_left(server_t *srv, connection_t *cl, regex_parse_t *parse);
void cmd_look(server_t *srv, connection_t *cl, regex_parse_t *parse);
void cmd_inventory(server_t *srv, connection_t *cl, regex_parse_t *parse);
void cmd_broadcast(server_t *srv, connection_t *cl, regex_parse_t *parse);
void cmd_connect_nbr(server_t *srv, connection_t *cl, regex_parse_t *parse);
void cmd_fork(server_t *srv, connection_t *cl, regex_parse_t *parse);
void cmd_eject(server_t *srv, connection_t *cl, regex_parse_t *parse);
void cmd_take(server_t *srv, connection_t *cl, regex_parse_t *parse);
void cmd_set(server_t *srv, connection_t *cl, regex_parse_t *parse);
void cmd_incantation(server_t *srv, connection_t *cl, regex_parse_t *parse);

void incantation_message(server_t *srv, connection_t *cl, player_t *ply);
void broadcast_gui(server_t *srv, char *fmt, ...);

// GUI commands
void bct(server_t *srv, connection_t *cl, int x, int y);
void cmd_bct(server_t *srv, connection_t *cl, regex_parse_t *parse);
void mct(server_t *srv, connection_t *cl);
void cmd_mct(server_t *srv, connection_t *cl, regex_parse_t *parse);
void msz(server_t *srv, connection_t *cl);
void cmd_msz(server_t *srv, connection_t *cl, regex_parse_t *parse);
void pin(server_t *srv, connection_t *cl);
void cmd_pin(server_t *srv, connection_t *cl, regex_parse_t *parse);
void plv(server_t *srv, connection_t *cl);
void cmd_plv(server_t *srv, connection_t *cl, regex_parse_t *parse);
void ppo(server_t *srv, connection_t *cl);
void cmd_ppo(server_t *srv, connection_t *cl, regex_parse_t *parse);
void sgt(server_t *srv, connection_t *cl);
void cmd_sgt(server_t *srv, connection_t *cl, regex_parse_t *parse);
void sst(server_t *srv, connection_t *cl, int time_unit);
void cmd_sst(server_t *srv, connection_t *cl, regex_parse_t *parse);
void tna(server_t *srv, connection_t *cl);
void cmd_tna(server_t *srv, connection_t *cl, regex_parse_t *parse);
/* Commands */

void pnw(server_t *srv, connection_t *cl, player_t *player);
void pex(server_t *srv, connection_t *cl, player_t *player);
void pbc(server_t *srv, connection_t *cl, player_t *player, char *msg);
void pic(server_t *srv, connection_t *cl, int *players_nb);
void pie(server_t *srv, connection_t *cl, player_t *player, char *result);
void pfk(server_t *srv, connection_t *cl, player_t *player);
void pdr(server_t *srv, connection_t *cl, player_t *player, int res);
void pgt(server_t *srv, connection_t *cl, player_t *player, int res);
void pdi(server_t *srv, connection_t *cl, player_t *player);
void enw(server_t *srv, connection_t *cl, egg_t *egg, player_t *player);
void ebo(server_t *srv, connection_t *cl, egg_t *egg);
void edi(server_t *srv, connection_t *cl, egg_t *egg);
void seg(server_t *srv, connection_t *cl, char *team_name);
void smg(server_t *srv, connection_t *cl, char *message);
void suc(server_t *srv, connection_t *cl);
void sbp(server_t *srv, connection_t *cl);

#endif /* !SERVER_H_ */
