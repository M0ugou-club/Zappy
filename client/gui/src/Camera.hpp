/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** Camera
*/

#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include <iostream>
#include <raylib/raylib-cpp.hpp>

class Camera {
    public:
        Camera();
        ~Camera();
        void create_camera();

    protected:
    private:
        Camera3D _camera;
        Vector3 _position;
        Vector3 _target;
        Vector3 _up;
        float _fovy;
        int _type;
};

#endif /* !CAMERA_HPP_ */
