/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** Map
*/

#ifndef MAP_HPP_
#define MAP_HPP_

#include "MyCube.hpp"

class Map {
    public:
        Map();
        Map(int x, int y);
        ~Map();
        void init_map();
        void draw();

    protected:
    private:
        int _x;
        int _y;

        std::vector<std::vector<MyCube>> _map;
};

#endif /* !MAP_HPP_ */
