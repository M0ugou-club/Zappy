/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** Player
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <iostream>
#include <vector>
#include <raylib/raylib-cpp.hpp>

class Player {
    public:
        Player(float x, float y, float z);
        ~Player() = default;

        inline raylib::Vector3 getPosition() { return _position; }
        inline int getLevel() { return _level; }
        inline void setPosition(raylib::Vector3 position) { _position = position; }
        inline void setColor(raylib::Color color) { _color = color; }
        inline void setBorderColor(Color color) { _border_color = color; }
        inline void setLevel(int level) { _level = level; }

        void draw();
        void move();

    protected:
    private:
        raylib::Vector3 _position = {};
        int _level = 1;

        raylib::Mesh _rectMesh = raylib::Mesh::Cube(1.0f, 1.0f, 1.0f);
        raylib::Model _rectModel = raylib::Model(_rectMesh);
        raylib::Color _color = raylib::Color::Black();
        Color _border_color = BLACK;
};

#endif /* !PLAYER_HPP_ */
