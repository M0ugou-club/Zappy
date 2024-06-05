/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** Player
*/

#include "Player.hpp"

Player::Player(float x, float y, float z)
{
    _position = raylib::Vector3(x, y, z);
}
