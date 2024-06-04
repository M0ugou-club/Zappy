/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** Map
*/

#include "Map.hpp"

Map::Map()
{
    _x = 4;
    _y = 4;
}

Map::Map(int x, int y)
{
    _x = x;
    _y = y;
}

Map::~Map()
{
}

void Map::init_map()
{
    bool color = false;

    for (int i = 0; i < _x; i++) {
        std::vector<MyCube> tmp;
        for (int j = 0; j < _y; j++) {
            MyCube cube;
            cube.set_position(Vector3{(float)i + 1, 0, (float)j});
            cube.set_color(color ? raylib::Color::White() : raylib::Color::Black());
            tmp.push_back(cube);
            color = !color;
        }
        _map.push_back(tmp);
        if (_y % 2 == 0)
            color = !color;
    }
}

void Map::draw()
{
    for (int i = 0; i < _x; i++) {
        for (int j = 0; j < _y; j++) {
            _map[i][j].draw();
        }
    }
}
