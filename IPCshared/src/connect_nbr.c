/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** connect_nbr
*/

#include <unistd.h>
#include <string.h>

void connect_nbr(int serv_fd)
{
    write(serv_fd, "Connect_nbr\n", strlen("Connect_nbr") + 1);
}
