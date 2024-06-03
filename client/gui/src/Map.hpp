/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** Map
*/

#ifndef MAP_HPP_
#define MAP_HPP_

#include <iostream>
#include <raylib/raylib-cpp.hpp>

class Map {
    public:
        Map(int x, int y);
        ~Map();
        void create_map();

    protected:
    private:
        int _x;
        int _y;
};

#endif /* !MAP_HPP_ */
