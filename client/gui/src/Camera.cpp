/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** Camera
*/

#include "Camera.hpp"

Camera::Camera()
{
    _camera = {0};
    _position = {0.0f, 10.0f, 10.0f};
    _target = {0.0f, 0.0f, 0.0f};
    _up = {0.0f, 1.0f, 0.0f};
    _fovy = 45.0f;
    _type = CAMERA_PERSPECTIVE;
}

Camera::~Camera()
{
}

void Camera::create_camera()
{
    _camera.position = _position;
    _camera.target = _target;
    _camera.up = _up;
    _camera.fovy = _fovy;
    _camera.projection = _type;
}
