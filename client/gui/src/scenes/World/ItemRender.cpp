/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** Item
*/

#include "ItemRender.hpp"

#include <raylib-cpp.hpp>

const std::map<ItemRender::ItemType, std::string> ItemRender::MODELFILENAMES = {
    {ItemRender::ItemType::FOOD, "food"},
    {ItemRender::ItemType::LINEMATE, "linemate"},
    {ItemRender::ItemType::DERAUMERE, "deraumere"},
    {ItemRender::ItemType::PHIRAS, "phiras"},
    {ItemRender::ItemType::MENDIANE, "mendiane"},
    {ItemRender::ItemType::SIBUR, "sibur"},
    {ItemRender::ItemType::THYSTAME, "thystame"},
};

ItemRender::ItemRender(ItemType type, int quantity, float y)
{
    _quantity = quantity;
    _type = type;
    _y = y;

    std::string obj_filename = "client/gui/assets/models/items/" + ItemRender::MODELFILENAMES.at(type) + ".obj";
    _cubeModel.Load(obj_filename);
    std::string texture_filename = "client/gui/assets/textures/items/" + ItemRender::MODELFILENAMES.at(type) + ".png";
    _texture.Load(texture_filename);
    _cubeModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = _texture;
}

void ItemRender::draw(raylib::Vector2 pos, float delta)
{
    float yFloatingAnim = sinf(GetTime() * 2.0f) * Y_FLOATING_ANIM_HEIGHT;
    _rotationAngle += ROTATION_SPEED * delta;
    _cubeModel.Draw(
        {pos.GetX(), _y + yFloatingAnim + ITEM_HEIGHT_OFFSET, pos.GetY()},
        {0.0f, 1.0f, 0.0f},
        _rotationAngle,
        {1.0f, 1.0f, 1.0f},
        WHITE
    );
    DrawCylinder({pos.GetX(), _y, pos.GetY()}, 0.5f, 0.01f, 0.001f, 30, {0, 0, 0, 170});
}
