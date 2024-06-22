/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** execute_commands
*/

#include "connection.h"
#include "server.h"

static const command_regex_t AI_COMMANDS[] = {
    {"Forward$", 7.0f, cmd_forward},
    {"Right$", 7.0f, cmd_right},
    {"Left$", 7.0f, cmd_left},
    {"Look$", 7.0f, cmd_look},
    {"Inventory$", 1.0f, cmd_inventory},
    {"Broadcast (.+)$", 7.0f, cmd_broadcast},
    {"Connect_nbr$", 0.0f, cmd_connect_nbr},
    {"Fork$", 42.0f, cmd_fork},
    {"Eject$", 7.0f, cmd_eject},
    {"Take ([a-z]+)$", 7.0f, cmd_take},
    {"Set ([a-z]+)$", 7.0f, cmd_set},
    {"Incantation$", 300.0f, cmd_incantation},
    {NULL, 0.0f, NULL}
};

static char *player_dequeue(connection_t *cl)
{
    char *cmd = NULL;

    if (cl->queue_size == 0)
        return NULL;
    cmd = cl->command_queue[0];
    for (int i = 0; i < cl->queue_size - 1; i++) {
        cl->command_queue[i] = cl->command_queue[i + 1];
    }
    cl->queue_size--;
    return cmd;
}

static void execute_ai_command(server_t *srv, connection_t *cl,
    player_t *ply, char *cmd)
{
    int regex_ret = 0;
    regex_t *regex = malloc(sizeof(regex_t));
    regex_parse_t parse = {0};

    parse.str = cmd;
    memset(parse.pmatch, 0, sizeof(parse.pmatch));
    for (int i = 0; AI_COMMANDS[i].command != NULL; i++) {
        regex_ret = regcomp(regex, AI_COMMANDS[i].command, REG_EXTENDED);
        regex_ret = regexec(regex, cmd, MAX_REGEX_MATCHES, parse.pmatch, 0);
        if (regex_ret == 0) {
            AI_COMMANDS[i].func(srv, cl, &parse);
            set_cooldown(&ply->action_cooldown,
                AI_COMMANDS[i].time / srv->args->frequency);
            regfree(regex);
            return;
        }
        regfree(regex);
    }
    SEND_FD(ply->fd, CMD_ERROR);
}

void execute_ai_commands(server_t *srv)
{
    connection_t *cl = NULL;
    char *cmd = NULL;

    for (player_t *tmp = srv->game->players; tmp; tmp = tmp->next) {
        if (tmp->incantation || !time_passed(&tmp->action_cooldown))
            continue;
        cl = get_client_by_fd(srv->cons, tmp->fd);
        if (!cl)
            continue;
        cmd = player_dequeue(cl);
        if (!cmd)
            continue;
        execute_ai_command(srv, cl, tmp, cmd);
        free(cmd);
    }
}

void player_enqueue(connection_t *cl, char *cmd)
{
    if (cl->queue_size >= MAX_COMMAND_QUEUE)
        return;
    cl->command_queue[cl->queue_size] = strdup(cmd);
    cl->queue_size++;
}
