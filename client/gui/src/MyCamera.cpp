/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** MyCamera
*/

#include "MyCamera.hpp"

MyCamera::MyCamera()
{
    _camera.position = _position;
    _camera.target = _target;
    _camera.up = _up;
    _camera.fovy = _fovy;
    _camera.projection = _type;
}

MyCamera::~MyCamera()
{
}
