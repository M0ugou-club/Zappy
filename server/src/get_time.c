/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** get_time
*/

#include "server.h"

bool time_passed(struct timeval *tv)
{
    struct timeval now;

    gettimeofday(&now, NULL);
    return (now.tv_sec > tv->tv_sec
        || (now.tv_sec == tv->tv_sec && now.tv_usec >= tv->tv_usec));
}

void set_cooldown(struct timeval *tv, float time)
{
    gettimeofday(tv, NULL);
    tv->tv_sec += (int)time;
    tv->tv_usec += (time - (int)time) * 1000000;
}
