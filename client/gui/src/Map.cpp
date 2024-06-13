/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** Map
*/

#include "Map.hpp"

Map::Map(int x, int y)
{
    _x = x;
    _y = y;
}

void Map::initMap()
{
    bool color = false;

    for (int i = 0; i < _x; i++) {
        std::vector<MyCube> tmp;
        for (int j = 0; j < _y; j++) {
            MyCube cube;
            cube.setPosition(raylib::Vector3{(float)i - (_x / 2.0f - 0.5f), 0, (float)j - (_y / 2.0f - 0.5f)});
            cube.setColor(color ? raylib::Color::White() : raylib::Color::Black());
            cube.setBorderColor(color ? BLACK : WHITE);
            tmp.push_back(cube);
            color = !color;
        }
        _map.push_back(tmp);
        if (_y % 2 == 0)
            color = !color;
    }
}

void Map::setSize(int x, int y)
{
    _x = x;
    _y = y;
    // _map.clear();
    // initMap();
}

void Map::draw()
{
    for (int i = 0; i < _x; i++) {
        for (int j = 0; j < _y; j++) {
            _map[i][j].draw();
        }
    }
}
