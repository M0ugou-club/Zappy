/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** forward
*/

#include <unistd.h>
#include <string.h>

void forward(int serv_fd)
{
    write(serv_fd, "Forward\n", strlen("Forward") + 1);
}
