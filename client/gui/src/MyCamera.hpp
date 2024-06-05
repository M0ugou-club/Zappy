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
        typedef enum move {
            LEFT,
            RIGHT,
            FORWARD,
            BACKWARD
        } move;
        MyCamera();
        ~MyCamera();
        raylib::Camera3D getCamera() { return _camera; }
        void moveCamera(move direction);

    protected:
    private:
        raylib::Camera3D _camera = {};
        raylib::Vector3 _position = {0.0f, 0.0f, 0.0f};
        raylib::Vector3 _target = {0.0f, 0.0f, 0.0f};
        raylib::Vector3 _up = {0.0f, 1.0f, 0.0f};
        float _fovy = 90.0f;
        int _type = CAMERA_PERSPECTIVE;
        float _distance_to_target = 6.5f;
        float _angle = 0.0f;
        float _speed = 0.01f;
};

#endif /* !MYCAMERA_HPP_ */
