/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** EnvironementShaders
*/

#include "LightManager.hpp"

LightManager::LightManager()
{
    _shader = new raylib::Shader("client/gui/assets/shaders/lighting.vs", "client/gui/assets/shaders/lighting.fs");

    _shader->locs[SHADER_LOC_VECTOR_VIEW] = _shader->GetLocation("viewPos");
    int ambientLoc = _shader->GetLocation("ambient");
    _shader->SetValue(ambientLoc, _ambient, SHADER_UNIFORM_VEC4);
}

LightManager::~LightManager()
{
    delete _shader;
}

raylib::Shader *LightManager::getShader()
{
    return _shader;
}

void LightManager::update(raylib::Camera3D camera)
{
    float cameraPosition[3] = {camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z};
    _shader->SetValue(_shader->locs[SHADER_LOC_VECTOR_VIEW], cameraPosition, SHADER_UNIFORM_VEC3);
    for (auto &light : _lights) {
        light.get()->update();
    }
}

void LightManager::addLight(raylib::Vector3 pos, Light::Type type, raylib::Color color, raylib::Vector3 target)
{
    if (_lights.size() >= MAX_LIGHTS)
        throw std::runtime_error("Max lights reached");
    _lights.push_back(std::make_unique<Light>(static_cast<int>(type), pos, target, color, _shader, _lights.size()));
}
