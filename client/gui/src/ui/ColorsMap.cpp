/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** ColorsMap
*/

#include "ColorsMap.hpp"

ColorsMap &ColorsMap::addColor(const std::string &name, const raylib::Color &color)
{
    colors[name] = color;
    return *this;
}

ColorsMap ColorsMap::defaultColors()
{
    ColorsMap colorsMap;

    colorsMap.addColor("default", raylib::Color::White());
    colorsMap.addColor("hover", raylib::Color::LightGray());
    colorsMap.addColor("press", raylib::Color::Gray());
    colorsMap.addColor("text", raylib::Color::Black());
    return colorsMap;
}
