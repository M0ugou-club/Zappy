/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** Player
*/

#include "Player.hpp"

const raylib::Vector3 Player::OFFSET = {0.5f, 1.0f, 0.5f};
const std::vector<raylib::Color> Player::COLORS = {
    raylib::Color::Red(),
    raylib::Color::Green(),
    raylib::Color::Blue(),
    raylib::Color::Yellow(),
    raylib::Color::Purple(),
    raylib::Color::Orange(),
    raylib::Color::Brown(),
    raylib::Color::Pink(),
    raylib::Color::White(),
    raylib::Color::Black(),
    raylib::Color::Gold(),
    raylib::Color::Lime(),
    raylib::Color::Maroon(),
    raylib::Color::Beige(),
    raylib::Color::Magenta(),
    raylib::Color::SkyBlue()
};

Player::Player(int teamIndex, const raylib::Vector2 mapSize)
    : _teamIdx(teamIndex), _mapSize(mapSize)
{
    _position.SetX(0.0f);
    _position.SetY(0.0f);
    _position.SetZ(0.0f);
    _rectangleMesh = GenMeshCube(_width, _height, _depth);
    _rectangleModel = LoadModelFromMesh(_rectangleMesh);
    _level = 1;
}

raylib::Color Player::getColor() const
{
    if (_teamIdx < 0 || _teamIdx >= COLORS.size())
        return raylib::Color::DarkPurple();
    return COLORS[_teamIdx];
}

Player::~Player()
{
}

void Player::draw() const
{
    DrawModel(_rectangleModel, _position + OFFSET - (raylib::Vector3(_mapSize.GetX() / 2, 0.0f, _mapSize.GetY() / 2)), 1.0f, getColor());
}
