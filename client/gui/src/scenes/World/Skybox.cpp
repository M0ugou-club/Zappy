/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** Skybox
*/

#include "Skybox.hpp"

const std::string Skybox::SHADERS_PATH = "bonus/assets/shaders/";
const std::string Skybox::TEXTURES_PATH = "bonus/assets/textures/";

Skybox::Skybox(std::string imagePath)
    :  _imagePath(imagePath), _cube(raylib::Mesh::Cube(1.0f, 1.0f, 1.0f)),
    _shader(raylib::Shader(SHADERS_PATH + "skybox.vs", SHADERS_PATH + "skybox.fs"))
{
    _skybox.Load(_cube);
    _cubemap.Load(TEXTURES_PATH + "skybox.png");
    _skybox.materials[0].maps[MATERIAL_MAP_CUBEMAP].texture = _cubemap;

    int mapType[1] = { MATERIAL_MAP_CUBEMAP };
    _shader.SetValue(GetShaderLocation(_shader, "environmentMap"), mapType, SHADER_UNIFORM_INT);
    _shader.SetValue(GetShaderLocation(_shader, "doGamma"), (int[1]){0}, SHADER_UNIFORM_INT);
}

void Skybox::draw() const
{
    rlDisableBackfaceCulling();
    rlDisableDepthMask();
    _skybox.Draw(_pos, 30.0f);
    rlEnableBackfaceCulling();
    rlEnableDepthMask();
}
