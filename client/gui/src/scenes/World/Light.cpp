/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** Light
*/

#include "Light.hpp"

Light::Light(int type, raylib::Vector3 pos, raylib::Vector3 target, raylib::Color color, raylib::Shader *shader, int id)
{
    _type = type;
    _position = pos;
    _target = target;
    _color = color;
    _enabled = true;

    _shader = shader;

    std::cout << "light " << id << " created" << std::endl;
    std::string this_light = "lights[" + std::to_string(id) + "]";
    std::cout << this_light << std::endl;
    _enabledLoc = _shader->GetLocation(std::string(this_light + ".enabled").c_str());
    _typeLoc = _shader->GetLocation(std::string(this_light + ".type").c_str());
    _positionLoc = _shader->GetLocation(std::string(this_light + ".position").c_str());
    _targetLoc = _shader->GetLocation(std::string(this_light + ".target").c_str());
    _colorLoc = _shader->GetLocation(std::string(this_light + ".color").c_str());
    updateShaderValues();
}

Light::~Light()
{
}

void Light::update()
{
    updateShaderValues();
}

void Light::updateShaderValues()
{
    _shader->SetValue(_enabledLoc, &_enabled, SHADER_UNIFORM_INT);
    _shader->SetValue(_typeLoc, &_type, SHADER_UNIFORM_INT);

    float position[3] = { _position.x, _position.y, _position.z };
    _shader->SetValue(_positionLoc, position, SHADER_UNIFORM_VEC3);
    float target[3] = { _target.x, _target.y, _target.z };
    _shader->SetValue(_targetLoc, target, SHADER_UNIFORM_VEC3);
    float color[4] = { (float)_color.r/255.0f, (float)_color.g/255.0f, (float)_color.b/255.0f, (float)_color.a/255.0f };
    _shader->SetValue(_colorLoc, color, SHADER_UNIFORM_VEC4);
}
