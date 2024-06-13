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
        Map(int x, int y);
        ~Map() = default;
        void initMap();
        void draw();

        void setSize(int x, int y);
        inline raylib::Vector2 getSize() const { return {static_cast<float>(_x), static_cast<float>(_y)}; }

    protected:
    private:
        int _x;
        int _y;

        std::vector<std::vector<MyCube>> _map;
};

#endif /* !MAP_HPP_ */
