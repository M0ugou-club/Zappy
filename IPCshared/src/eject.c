/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** eject
*/

#include <unistd.h>
#include <string.h>

void eject(int serv_fd)
{
    write(serv_fd, "Eject\n", strlen("Eject") + 1);
}
