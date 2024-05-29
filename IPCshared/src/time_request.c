/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** time_request
*/

#include <unistd.h>
#include <string.h>

void time_request(int serv_fd)
{
    write(serv_fd, "sgt\n", strlen("sgt") + 1);
}
