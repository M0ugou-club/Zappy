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

MyCamera::~MyCamera()
{
}

void MyCamera::moveCamera(move direction)
{
    if (direction == LEFT) {
        _angle += _speed;
    }
    if (direction == RIGHT) {
        _angle -= _speed;
    }
    if (direction == FORWARD) {
        _distance_to_target -= _speed * 4;
    }
    if (direction == BACKWARD) {
        _distance_to_target += _speed * 4;
    }

    _position.y = _distance_to_target;
    _position.x = _distance_to_target * cos(_angle);
    _position.z = _distance_to_target * sin(_angle);

    _camera.position = _position;
}