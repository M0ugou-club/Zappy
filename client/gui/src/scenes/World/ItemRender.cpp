/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** Item
*/

#include "ItemRender.hpp"

const raylib::Vector3 ItemRender::OFFSET = {0.5f, 0.0f, 0.5f};
const std::map<ItemRender::ItemType, std::string> ItemRender::MODEL_FILENAMES = {
    {ItemRender::ItemType::FOOD, "food"},
    {ItemRender::ItemType::LINEMATE, "linemate"},
    {ItemRender::ItemType::DERAUMERE, "deraumere"},
    {ItemRender::ItemType::PHIRAS, "phiras"},
    {ItemRender::ItemType::MENDIANE, "mendiane"},
    {ItemRender::ItemType::SIBUR, "sibur"},
    {ItemRender::ItemType::THYSTAME, "thystame"},
};

const std::map<ItemRender::ItemType, raylib::Vector2> ItemRender::ITEMS_OFFSETS = {
    {ItemRender::ItemType::FOOD, {0.2f, 0.0f}},
    {ItemRender::ItemType::LINEMATE, {0.0f, 0.2f}},
    {ItemRender::ItemType::DERAUMERE, {-0.2f, 0.0f}},
    {ItemRender::ItemType::PHIRAS, {0.0f, -0.2f}},
    {ItemRender::ItemType::MENDIANE, {0.2f, 0.2f}},
    {ItemRender::ItemType::SIBUR, {-0.2f, -0.2f}},
    {ItemRender::ItemType::THYSTAME, {0.0f, 0.0f}},
};

ItemRender::ItemRender(const ItemType type, const raylib::Vector2 mapSize, int quantity, float y)
{
    _type = type;
    _mapSize = mapSize;
    _quantity = quantity;
    _y = y;

    std::string obj_filename = "bonus/assets/models/items/" + ItemRender::MODEL_FILENAMES.at(type) + ".obj";
    _cubeModel.Load(obj_filename);
    std::string texture_filename = "bonus/assets/textures/items/" + ItemRender::MODEL_FILENAMES.at(type) + ".png";
    _texture.Load(texture_filename);
    _cubeModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = _texture;
}

float ItemRender::getOffsetRotationSeed(raylib::Vector2 pos)
{
    std::string combined = std::to_string(pos.GetX()) + "," + std::to_string(pos.GetY()) + ", " + std::to_string(_mapSize.GetX()) + ", " + std::to_string(_mapSize.GetY()) + ", " + std::to_string((int)_type);
    std::size_t hash = std::hash<std::string>{}(combined);

    float hash_float = static_cast<float>(hash) / static_cast<float>(std::numeric_limits<std::size_t>::max());
    return hash_float;
}

void ItemRender::draw(raylib::Vector2 pos, int amount)
{
    float movementSeed = getOffsetRotationSeed(pos);
    raylib::Vector3 pos3d = {pos.GetX(), 0.0f, pos.GetY()};
    raylib::Vector3 final_pos = pos3d + OFFSET - (raylib::Vector3(_mapSize.GetX() / 2, 0.0f, _mapSize.GetY() / 2));
    final_pos.SetX(final_pos.GetX() + ITEMS_OFFSETS.at(_type).GetX());
    final_pos.SetZ(final_pos.GetZ() + ITEMS_OFFSETS.at(_type).GetY());
    final_pos.SetY(_y);
    float yFloatingAnim = sinf((GetTime() + (movementSeed * 128.0f)) * 2.0f) * Y_FLOATING_ANIM_HEIGHT;
    DrawCylinder(final_pos, 0.1f, 0.01f, 0.001f, 30, {0, 0, 0, 110});
    for (int i = 0; i < amount; i++) {
        _cubeModel.Draw(
            {final_pos.GetX(), final_pos.GetY() + yFloatingAnim + (ITEM_HEIGHT_OFFSET * (i * 3)) + ITEM_HEIGHT_OFFSET, final_pos.GetZ()},
            {0.0f, 1.0f, 0.0f},
            (GetTime() * ROTATION_SPEED) + (movementSeed * 256.0f),
            {0.3f, 0.3f, 0.3f},
            WHITE
        );
    }
}
