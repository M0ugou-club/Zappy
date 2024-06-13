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
#include <raylib-cpp.hpp>

class Player {
    public:
        static constexpr float SIZE = 1.5f;

        Player(int teamIndex, const raylib::Vector2 mapSize);
        ~Player();

        inline raylib::Vector3 getPosition() const { return _position; }
        inline int getLevel() const { return _level; }
        inline void setPosition(raylib::Vector3 position) { _position = position; }
        inline void setLevel(int level) { _level = level; }
        inline void setOrientation(int orientation) { _orientation = orientation; }

        void draw() const;
        void move();
        raylib::Color getColor() const;

        static const raylib::Vector3 OFFSET;
        static const std::vector<raylib::Color> COLORS;

    private:
        float _width = 0.5f;
        float _height = 0.5f;
        float _depth = 0.5f;
        raylib::Vector3 _position = {0.0f, 0.0f, 0.0f};
        Mesh _rectangleMesh = GenMeshCube(_width, _height, _depth);
        Model _rectangleModel = LoadModelFromMesh(_rectangleMesh);
        int _teamIdx = 0;
        int _level = 1;
        int _orientation = 0;
        const raylib::Vector2 _mapSize;
};

#endif /* !PLAYER_HPP_ */
