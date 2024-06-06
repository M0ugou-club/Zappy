/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** execute_connections
*/

#include "server.h"

static const command_regex_t CMDS[] = {
    {"Forward$", NULL},
    {"Right$", NULL},
    {"Left$", NULL},
    {"Look$", NULL},
    {"Inventory$", NULL},
    {"Broadcast (.+)$", NULL},
    {"Connect_nbr$", NULL},
    {"Fork$", NULL},
    {"Eject$", NULL},
    {"Take ([a-z]+)$", NULL},
    {"Set ([a-z]+)$", NULL},
    {"Incantation$", NULL},
    {NULL, NULL}
};

static char *get_arg(const char *src, size_t start, size_t end)
{
    char *dest = malloc(end - start + 1);

    if (dest == NULL)
        return NULL;
    memset(dest, 0, end - start + 1);
    for (size_t i = start; i < end; i++)
        dest[i - start] = src[i];
    return dest;
}

static void replace_cr(char *str)
{
    for (size_t i = 0; str[i] != '\0'; i++)
        if (str[i] == '\r')
            str[i] = '\0';
}

static void execute(char *cmd, int client_fd, server_t *srv)
{
    int regex_ret = 0;
    regex_t *regex = malloc(sizeof(regex_t));
    regex_parse_t parse = {0};

    replace_cr(cmd);
    parse.str = cmd;
    memset(parse.pmatch, 0, sizeof(parse.pmatch));
    for (int i = 0; CMDS[i].command != NULL; i++) {
        regex_ret = regcomp(regex, CMDS[i].command, REG_EXTENDED);
        if (regex_ret != 0)
            continue;
        regex_ret = regexec(regex, cmd, MAX_REGEX_MATCHES, parse.pmatch, 0);
        if (regex_ret == 0) {
            CMDS[i].func(srv, get_client_by_fd(srv->cons, client_fd), &parse);
            regfree(regex);
            return;
        }
        regfree(regex);
    }
    SEND_FD(client_fd, CMD_ERROR);
}

static char *new_buffer(connection_t *client, char *tmp)
{
    char *tmp2 = NULL;

    if (tmp - client->buffer - 2 <= 0) {
        free(client->buffer);
        return NULL;
    }
    tmp2 = malloc(tmp - client->buffer - 2);
    if (tmp2 == NULL)
        return NULL;
    memset(tmp2, 0, tmp - client->buffer - 2);
    memcpy(tmp2, tmp + 2, tmp - client->buffer - 2);
    free(client->buffer);
    return tmp2;
}

static void execute_client(connection_t *client, server_t *srv)
{
    char *tmp = NULL;
    char *tmp2 = NULL;

    if (client->buffer == NULL)
        return;
    tmp = strstr(client->buffer, "\n");
    if (tmp == NULL)
        return;
    tmp2 = get_arg(client->buffer, 0, tmp - client->buffer);
    if (tmp2 == NULL)
        return;
    if (*tmp2 != '\0')
        execute(tmp2, client->fd, srv);
    if (client->buffer != NULL)
        client->buffer = new_buffer(client, tmp);
    free(tmp2);
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