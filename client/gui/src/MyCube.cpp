/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** MyCube
*/

#include "MyCube.hpp"

MyCube::MyCube()
{
}

MyCube::~MyCube()
{
}

void MyCube::draw()
{
    DrawCube(_position, _size.x, _size.y, _size.z, _color);
    DrawCubeWires(_position, _size.x, _size.y, _size.z, _border_color);
}