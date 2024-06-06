/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** main
*/

#include "Gui.hpp"
#include "Args.hpp"

int main(int ac, char **av)
{
    Gui gui;

    Args::main_example(ac, av);
    gui.start();
    return 0;
}
