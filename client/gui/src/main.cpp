/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** main
*/

#include "Core.hpp"
#include "Args.hpp"

int main(int ac, char **av)
{
    Core core;

    Args::main_example(ac, av);
    core.start();
    return 0;
}
