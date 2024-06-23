/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** execute_connections
*/

#include "server.h"

static const command_regex_t GRAPHICAL_COMMANDS[] = {
    {"msz$", -1.0f, cmd_msz},
    {"bct ([0-9]+) ([0-9]+)$", -1.0f, cmd_bct},
    {"mct$", -1.0f, cmd_mct},
    {"tna$", -1.0f, cmd_tna},
    {"ppo #([0-9]+)$", -1.0f, cmd_ppo},
    {"plv #([0-9]+)$", -1.0f, cmd_plv},
    {"pin #([0-9]+)$", -1.0f, cmd_pin},
    {"sgt$", -1.0f, cmd_sgt},
    {"sst ([0-9]+)$", -1.0f, cmd_sst},
    {NULL, 0.0f, NULL}
};

static void execute_command(const command_regex_t *cmd, server_t *srv,
    int client_fd, regex_parse_t parse)
{
    connection_t *client = get_client_by_fd(srv->cons, client_fd);

    if (client == NULL)
        return;
    cmd->func(srv, client, &parse);
}

static void execute_graphical(char *cmd, int client_fd, server_t *srv)
{
    int regex_ret = 0;
    regex_t *regex = malloc(sizeof(regex_t));
    regex_parse_t parse = {0};

    parse.str = cmd;
    memset(parse.pmatch, 0, sizeof(parse.pmatch));
    for (int i = 0; GRAPHICAL_COMMANDS[i].command != NULL; i++) {
        regex_ret =
            regcomp(regex, GRAPHICAL_COMMANDS[i].command, REG_EXTENDED);
        if (regex_ret != 0)
            continue;
        regex_ret = regexec(regex, cmd, MAX_REGEX_MATCHES, parse.pmatch, 0);
        if (regex_ret == 0) {
            execute_command(&GRAPHICAL_COMMANDS[i], srv, client_fd, parse);
            regfree(regex);
            return;
        }
        regfree(regex);
    }
    SEND_FD(client_fd, CMD_ERROR);
}

static void execute_client(connection_t *cli, server_t *srv)
{
    char *cmd = get_packet(&cli->buffer, &cli->buffer_size);

    if (cmd == NULL || cli->team == NULL)
        return;
    if (strcmp(cli->team, GRAPHIC_TEAM) == 0)
        execute_graphical(cmd, cli->fd, srv);
    else
        player_enqueue(cli, cmd);
    free(cmd);
}

void execute_connections(server_t *srv)
{
    connection_t *tmp = srv->cons;

    while (tmp != NULL) {
        if (FD_ISSET(tmp->fd, srv->writefds))
            execute_client(tmp, srv);
        tmp = tmp->next;
    }
}
