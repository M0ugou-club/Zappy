/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** get_time
*/

#include "server.h"

long get_time(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return ((long)(tv.tv_sec * 1000 + tv.tv_usec / 1000));
}
