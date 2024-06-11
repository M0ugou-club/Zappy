/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** Player
*/

#include "Player.hpp"

const raylib::Vector3 Player::OFFSET = {0.5f, 1.0f, 0.5f};

Player::Player()
{
    _position.SetX(0.0f);
    _position.SetY(0.0f);
    _position.SetZ(0.0f);
    _rectangleMesh = GenMeshCube(_width, _height, _depth);
    _rectangleModel = LoadModelFromMesh(_rectangleMesh);
    _color = raylib::Color::Black();
    _level = 1;
}

Player::~Player()
{
}

void Player::draw() const
{
    DrawModel(_rectangleModel, _position + OFFSET, 1.0f, raylib::Color::Pink());
}

void Player::move()
{
}
