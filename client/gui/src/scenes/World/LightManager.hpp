/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** EnvironementShaders
*/

#ifndef LIGHTMANAGER_HPP_
    #define LIGHTMANAGER_HPP_

    #include <raylib-cpp.hpp>
    #include <iostream>
    #include <memory>

    #include "Light.hpp"

class LightManager {
    public:
        static constexpr int MAX_LIGHTS = 4;

        LightManager();
        ~LightManager();

        raylib::Shader *getShader();
        void addLight(raylib::Vector3 pos, Light::Type type = Light::Type::LIGHT_POINT,
            raylib::Color color = raylib::Color::White(), raylib::Vector3 target = raylib::Vector3(0, 0, 0));
        void update(raylib::Camera3D camera);

    private:
        raylib::Shader *_shader;
        std::vector<std::unique_ptr<Light>> _lights;

        float _ambient[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
};

#endif /* !LIGHTMANAGER_HPP_ */
