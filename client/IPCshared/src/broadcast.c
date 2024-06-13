/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** broadcast
*/

#include <unistd.h>
#include <string.h>

void broadcast(int serv_fd, char *message)
{
    write(serv_fd, "Broadcast ", strlen("Broadcast "));
    write(serv_fd, message, strlen(message));
    write(serv_fd, "\n", 1);
}
