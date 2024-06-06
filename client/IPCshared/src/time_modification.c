/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** time_modification
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

void time_modification(int serv_fd, int time)
{
    char *str = malloc(sizeof(char) * 10);

    sprintf(str, "sst %d\n", time);
    write(serv_fd, str, strlen(str));
}
