/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** send_message
*/

#include "server.h"
#include <stdarg.h>

int get_array_size(char **arr)
{
    int i = 0;

    if (arr == NULL)
        return 0;
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

void queue_formatted_message(connection_t *conn, const char *fmt, ...)
{
    va_list args;
    char *msg;
    size_t size = 0;

    va_start(args, fmt);
    size = vsnprintf(NULL, 0, fmt, args);
    va_end(args);
    msg = malloc(size + 1);
    if (msg == NULL)
        return;
    va_start(args, fmt);
    vsnprintf(msg, size + 1, fmt, args);
    va_end(args);
    queue_message(conn, msg);
    free(msg);
}

void send_formatted_message(connection_t *conn, const char *fmt, ...)
{
    va_list args;
    char *msg;
    size_t size = 0;

    size = snprintf(NULL, 0, fmt, args);
    msg = malloc(size + 1);
    va_start(args, fmt);
    vsprintf(msg, fmt, args);
    va_end(args);
    SEND(conn, msg);
    free(msg);
}
