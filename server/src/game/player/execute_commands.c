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

    if (!cl->command_queue[0])
        return NULL;
    cmd = strdup(cl->command_queue[0]);
    free(cl->command_queue[0]);
    for (int i = 0; i < MAX_COMMAND_QUEUE - 1; i++) {
        cl->command_queue[i] = cl->command_queue[i + 1];
    }
    cl->command_queue[MAX_COMMAND_QUEUE - 1] = NULL;
    return cmd;
}

static void execute_ai_command(server_t *srv, connection_t *cl, player_t *ply, char *cmd)
{
    int regex_ret = 0;
    regex_t *regex = malloc(sizeof(regex_t));
    regex_parse_t parse = {0};

    parse.str = cmd;
    memset(parse.pmatch, 0, sizeof(parse.pmatch));
    for (int i = 0; AI_COMMANDS[i].command != NULL; i++) {
        regex_ret = regcomp(regex, AI_COMMANDS[i].command, REG_EXTENDED);
        if (regex_ret != 0)
            continue;
        regex_ret = regexec(regex, cmd, MAX_REGEX_MATCHES, parse.pmatch, 0);
        if (regex_ret == 0) {
            AI_COMMANDS[i].func(srv, cl, &parse);
            ply->action_cooldown = get_time() + CALC_TIME(AI_COMMANDS[i].time / srv->args->frequency);
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

    for (player_t *tmp = srv->game->players; tmp; tmp = tmp->next) {
        if (get_time() < tmp->action_cooldown)
            continue;
        cl = get_client_by_fd(srv->cons, tmp->fd);
        char *cmd = player_dequeue(cl);
        if (!cmd)
            continue;
        execute_ai_command(srv, cl, tmp, cmd);
        free(cmd);
    }
}

static int queue_item_count(connection_t *cl)
{
    int count = 0;

    while (cl->command_queue[count] && count < MAX_COMMAND_QUEUE) {
        count++;
    }
    return count;
}

void player_enqueue(connection_t *cl, char *cmd)
{
    if (queue_item_count(cl) >= MAX_COMMAND_QUEUE)
        return;
    for (int i = 0; i < MAX_COMMAND_QUEUE; i++) {
        if (!cl->command_queue[i]) {
            cl->command_queue[i] = strdup(cmd);
            break;
        }
    }
}
