/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** Item
*/

#include "Item.hpp"

#include <raylib-cpp.hpp>

const std::map<Item::ItemType, std::string> Item::MODELFILENAMES = {
    {FOOD, "food"},
    {LINEMATE, "linemate"},
    {DERAUMERE, "deraumere"},
    {PHIRAS, "phiras"},
    {MENDIANE, "mendiane"},
    {SIBUR, "sibur"},
    {THYSTAME, "thystame"},
};

Item::Item(float x, float y, float z, ItemType type, int quantity)
{
    _position.SetX(x);
    _position.SetY(y);
    _position.SetZ(z);
    _quantity = quantity;
    _type = type;

    std::string obj_filename = "client/gui/assets/models/items/" + Item::MODELFILENAMES.at(type) + ".obj";
    _cubeModel.Load(obj_filename);
    std::string texture_filename = "client/gui/assets/textures/items/" + Item::MODELFILENAMES.at(type) + ".png";
    _texture.Load(texture_filename);
    _cubeModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = _texture;
}

void Item::draw(float delta)
{
    float yFloatingAnim = sinf(GetTime() * 2.0f) * Y_FLOATING_ANIM_HEIGHT;
    _rotationAngle += ROTATION_SPEED * delta;
    _cubeModel.Draw(
        {_position.GetX(), _position.GetY() + yFloatingAnim + ITEM_HEIGHT_OFFSET, _position.GetZ()},
        {0.0f, 1.0f, 0.0f},
        _rotationAngle,
        {1.0f, 1.0f, 1.0f},
        WHITE
    );
    DrawCylinder(_position, 0.5f, 0.01f, 0.001f, 30, {0, 0, 0, 170});
}
