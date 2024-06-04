/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** MyCamera
*/

#ifndef MYCAMERA_HPP_
#define MYCAMERA_HPP_

#include <iostream>
#include <vector>
#include <raylib/raylib-cpp.hpp>

class MyCamera {
    public:
        MyCamera();
        ~MyCamera();
        Camera3D get_camera() { return _camera; }

    protected:
    private:
        Camera3D _camera = {};
        Vector3 _position = {0.0f, 10.0f, 10.0f};
        Vector3 _target = {0.0f, 0.0f, 0.0f};
        Vector3 _up = {0.0f, 1.0f, 0.0f};
        float _fovy = 45.0f;
        int _type = CAMERA_PERSPECTIVE;
};

#endif /* !MYCAMERA_HPP_ */     
