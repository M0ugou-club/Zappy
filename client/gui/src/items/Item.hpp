/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** Item
*/

#ifndef ITEM_HPP_
    #define ITEM_HPP_

#include <raylib-cpp.hpp>

class Item {
    public:
        static constexpr float Y_FLOATING_ANIM_HEIGHT = 0.3f;
        static constexpr float ROTATION_SPEED = 16.0f;
        static constexpr float SIZE = 1.5f;
        static constexpr float ITEM_HEIGHT_OFFSET = 1.5f;

        Item(float x, float y, float z, int quantity = 1);
        ~Item() = default;

        void draw(float delta = 0);
        void setPosition(float x, float y, float z);

    private:
        raylib::Vector3 _position = {};
        int _quantity;

        raylib::Mesh _cubeMesh = raylib::Mesh::Cube(SIZE, SIZE, SIZE / 10);
        raylib::Model _cubeModel = raylib::Model(_cubeMesh);
        float _rotationAngle = 0.0f;
};

#endif /* !ITEM_HPP_ */
