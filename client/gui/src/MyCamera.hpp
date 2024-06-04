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
            ZOOM_IN,
            ZOOM_OUT
        } move;
        MyCamera();
        ~MyCamera();
        raylib::Camera3D get_camera() { return _camera; }
        void move_camera(move direction);

    protected:
    private:
        raylib::Camera3D _camera = {};
        Vector3 _position = {0.0f, 10.0f, 10.0f};
        Vector3 _target = {0.0f, 0.0f, 0.0f};
        Vector3 _up = {0.0f, 1.0f, 0.0f};
        float _fovy = 45.0f;
        int _type = CAMERA_PERSPECTIVE;
        float _distance_to_target = 10.0f;
        float _angle = 0.0f;
        float _speed = 0.01f;
};

#endif /* !MYCAMERA_HPP_ */
