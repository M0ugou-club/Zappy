/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** send_message
*/

#include "server.h"

int get_array_size(char **arr)
{
    int i = 0;

    while (arr[i] != NULL)
        i++;
    return i;
}

void queue_message(connection_t *conn, char *msg)
{
    int size = get_array_size(conn->send_queue);

    conn->send_queue = realloc(
        conn->send_queue, sizeof(char *) * (size + 2));
    conn->send_queue[size] = strdup(msg);
    conn->send_queue[size + 1] = NULL;
}
