/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** Item
*/

#include "Item.hpp"

#include <raylib/raylib-cpp.hpp>

Item::Item(float x, float y, float z, int quantity)
{
    _position.SetX(x);
    _position.SetY(y);
    _position.SetZ(z);
    _quantity = quantity;
}

Item::~Item()
{
    UnloadModel(_cubeModel);
}

void Item::draw(float delta)
{
    _rotationAngle += ROTATION_SPEED * delta;
    float yFloatingAnim = sinf(GetTime() * 2.0f) * Y_FLOATING_ANIM_HEIGHT;
    DrawModelEx(
        _cubeModel,
        {_position.GetX(), _position.GetY() + yFloatingAnim + ITEM_HEIGHT_OFFSET, _position.GetZ()},
        {0.0f, 1.0f, 0.0f},
        _rotationAngle,
        {1.0f, 1.0f, 1.0f},
        BLACK
    );
    DrawCylinder(_position, 0.5f, 0.01f, 0.001f, 30, {0, 0, 0, 170});
}
