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

        static const std::vector<std::string> MODELS;

        Player(int teamIndex, const raylib::Vector2 &mapSize);
        ~Player();

        inline raylib::Vector3 getPosition() const { return _position; }
        inline int getLevel() const { return _level; }
        inline void setPosition(raylib::Vector3 position) { _position = position; }
        void setLevel(int level);
        inline void setIncantating(bool incantating) { _incantating = incantating; }
        inline void setOrientation(int orientation) { _orientation = orientation; }
        inline void setMessage(const std::string &message) { _message = message; }

        void draw() const;
        raylib::Color getColor() const;

        static const raylib::Vector3 OFFSET;
        static const std::vector<raylib::Color> COLORS;

    private:
        float _width = 0.5f;
        float _height = 0.5f;
        float _depth = 0.5f;
        raylib::Vector3 _position = {0.0f, 0.0f, 0.0f};
        raylib::Model _model;
        int _teamIdx = 0;
        int _level = 1;
        int _orientation = 0;
        bool _incantating = false;
        const raylib::Vector2 _mapSize;
        std::string _message;
};

#endif /* !PLAYER_HPP_ */
