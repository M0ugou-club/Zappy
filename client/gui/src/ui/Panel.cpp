/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** Panel
*/

#include "Panel.hpp"

Panel::Panel(std::string skin, const raylib::Vector2 &position, const raylib::Vector2 &size, const ColorsMap &colors)
    : _position(position), _size(size), _colorMap(colors)
{
    _sprite.Load("client/gui/assets/" + skin);
    _sourceRec = raylib::Rectangle(0, 0, _sprite.width, _sprite.height);
    _destRec = raylib::Rectangle(_position.x, _position.y, _size.x, _size.y);
    _npatchInfo.left = 12;
    _npatchInfo.top = 12;
    _npatchInfo.right = 12;
    _npatchInfo.bottom = 12;
    _npatchInfo.source = _sourceRec;
}

Panel::~Panel()
{
}

void Panel::draw(std::string color)
{
    raylib::Vector2 origin = raylib::Vector2(0, 0);
    float rotation = 0;
    DrawTextureNPatch(_sprite, _npatchInfo, _destRec, origin, rotation, _colorMap[color]);
}
