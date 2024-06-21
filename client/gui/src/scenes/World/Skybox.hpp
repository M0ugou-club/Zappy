/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** Skybox
*/

#ifndef SKYBOX_HPP_
#define SKYBOX_HPP_

#include <raylib-cpp.hpp>
#include <rlgl.h>

class Skybox {
    public:
        static const std::string SHADERS_PATH;
        static const std::string TEXTURES_PATH;

        Skybox(std::string imagePath);
        ~Skybox() = default;

        void draw() const;

    private:
        std::string _imagePath;
        raylib::Vector3 _pos;

        raylib::TextureCubemap _cubemap;
        raylib::Mesh _cube;
        raylib::Model _skybox;
        raylib::Shader _shader;
};

#endif /* !SKYBOX_HPP_ */
