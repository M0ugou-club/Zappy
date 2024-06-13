/*
** EPITECH PROJECT, 2024
** Zappy
** File description:
** ColorsMap
*/

#ifndef COLORSMAP_HPP_
    #define COLORSMAP_HPP_

    #include "raylib-cpp.hpp"
    #include <map>
    #include <iterator>

class ColorsMap {
    public:
        ColorsMap() = default;
        ~ColorsMap() = default;

        ColorsMap &addColor(const std::string &name, const raylib::Color &color);

        raylib::Color operator[](const std::string &name) const { return colors.at(name); }

        std::map<std::string, raylib::Color>::iterator begin() { return colors.begin(); }
        std::map<std::string, raylib::Color>::iterator end() { return colors.end(); }

        static ColorsMap defaultColors();

        std::map<std::string, raylib::Color> colors;
};

#endif /* !COLORSMAP_HPP_ */
