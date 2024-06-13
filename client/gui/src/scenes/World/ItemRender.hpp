/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** Item
*/

#ifndef ITEM_HPP_
    #define ITEM_HPP_

#include <raylib-cpp.hpp>
#include <map>

class ItemRender {
    public:

        enum class ItemType {
            FOOD,
            LINEMATE,
            DERAUMERE,
            PHIRAS,
            MENDIANE,
            SIBUR,
            THYSTAME,
        };

        static constexpr float Y_FLOATING_ANIM_HEIGHT = 0.1f;
        static constexpr float ROTATION_SPEED = 16.0f;
        static constexpr float ITEM_HEIGHT_OFFSET = 0.2f;

        static const raylib::Vector3 OFFSET;
        static const std::map<ItemType, std::string> MODELFILENAMES;

        static std::string GetPathFromType(ItemType type);

        ItemRender(const ItemType type, const raylib::Vector2 mapSize, int quantity = 1, float y = 0.53f);
        ~ItemRender() = default;

        void draw(raylib::Vector2 pos, float delta = 0);
        void setPosition(float x, float y, float z);

    private:
        ItemType _type;
        raylib::Vector2 _mapSize;
        int _quantity;
        float _y;

        raylib::Model _cubeModel;
        raylib::Texture _texture;
        float _rotationAngle = 0.0f;
};

#endif /* !ITEM_HPP_ */
