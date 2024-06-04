/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** left
*/

#include <unistd.h>
#include <string.h>

void left(int serv_fd)
{
    write(serv_fd, "Left\n", strlen("Left") + 1);
}
