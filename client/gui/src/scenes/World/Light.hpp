/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** Light
*/

#ifndef LIGHT_HPP_
    #define LIGHT_HPP_

    #include <raylib-cpp.hpp>
    #include <iostream>

class Light {
    public:
        enum class Type {
            LIGHT_DIRECTIONAL = 0,
            LIGHT_POINT
        };

        Light(int type, raylib::Vector3 pos, raylib::Vector3 target, raylib::Color color, raylib::Shader *shader, int id);
        ~Light();

        void update();
        void updateShaderValues();

    private:
        raylib::Shader *_shader;
        int _id;

        int _type;
        bool _enabled;
        Vector3 _position;
        Vector3 _target;
        Color _color;

        int _enabledLoc;
        int _typeLoc;
        int _positionLoc;
        int _targetLoc;
        int _colorLoc;
};

#endif /* !LIGHT_HPP_ */
