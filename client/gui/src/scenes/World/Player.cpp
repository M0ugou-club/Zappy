/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** Player
*/

#include "Player.hpp"

Player::Player()
{
    _position.SetX(0.0f);
    _position.SetY(10.0f);
    _position.SetZ(0.0f);
    rectangleMesh = GenMeshCube(width, height, depth);
    rectangleModel = LoadModelFromMesh(rectangleMesh);
    _color = raylib::Color::Black();
    _level = 1;
}

Player::~Player()
{
}

void Player::draw() const
{
    DrawModel(rectangleModel, _position, 1.0f, WHITE);
}

void Player::move()
{
}
