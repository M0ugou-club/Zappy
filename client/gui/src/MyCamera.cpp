/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** MyCamera
*/

#include "MyCamera.hpp"

MyCamera::MyCamera()
{
    _position.y = _distance_to_target;
    _position.x = _distance_to_target * cos(_angle);
    _position.z = _distance_to_target * sin(_angle);
    _camera.position = _position;
    _camera.target = _target;
    _camera.up = _up;
    _camera.fovy = _fovy;
    _camera.projection = _type;
}

void MyCamera::moveCamera(Direction direction)
{
    if (direction == Direction::LEFT) {
        _angle += _speed;
    }
    if (direction == Direction::RIGHT) {
        _angle -= _speed;
    }
    if (direction == Direction::FORWARD) {
        _distance_to_target -= _speed * 4;
    }
    if (direction == Direction::BACKWARD) {
        _distance_to_target += _speed * 4;
    }

    _position.y = _distance_to_target;
    _position.x = _distance_to_target * cos(_angle);
    _position.z = _distance_to_target * sin(_angle);

    _camera.position = _position;
}

void MyCamera::updateCamera()
{
    if(IsKeyDown(KEY_W))
        moveCamera(Direction::FORWARD);
    if(IsKeyDown(KEY_S))
        moveCamera(Direction::BACKWARD);
    if(IsKeyDown(KEY_A))
        moveCamera(Direction::LEFT);
    if(IsKeyDown(KEY_D))
        moveCamera(Direction::RIGHT);
}