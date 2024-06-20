/*
** EPITECH PROJECT, 2024
** Zappy [WSL: Fedora]
** File description:
** Player
*/

#include "Player.hpp"


const raylib::Vector3 Player::OFFSET = {0.5f, 0.5f, 0.5f};
const std::vector<std::string> Player::MODELS = {
    "bonus/assets/models/player/pawn.obj",
    "bonus/assets/models/player/knight.obj",
    "bonus/assets/models/player/pawn.obj",
    "bonus/assets/models/player/knight.obj",
    "bonus/assets/models/player/bishop.obj",
    "bonus/assets/models/player/tower.obj",
    "bonus/assets/models/player/queen.obj",
    "bonus/assets/models/player/king.obj",
};

const std::vector<raylib::Color> Player::COLORS = {
    raylib::Color::Red(),
    raylib::Color::Green(),
    raylib::Color::Blue(),
    raylib::Color::Yellow(),
    raylib::Color::Purple(),
    raylib::Color::Orange(),
    raylib::Color::Brown(),
    raylib::Color::Pink(),
    raylib::Color::White(),
    raylib::Color::Black(),
    raylib::Color::Gold(),
    raylib::Color::Lime(),
    raylib::Color::Maroon(),
    raylib::Color::Beige(),
    raylib::Color::Magenta(),
    raylib::Color::SkyBlue()
};

Player::Player(int teamIndex, const raylib::Vector2 &mapSize)
    : _teamIdx(teamIndex), _mapSize(mapSize)
{
    _position.SetX(0.0f);
    _position.SetY(0.0f);
    _position.SetZ(0.0f);
    _model.Load("bonus/assets/models/player/knight.obj");
    _level = 1;
}

raylib::Color Player::getColor() const
{
    if (_teamIdx < 0 || _teamIdx >= COLORS.size())
        return raylib::Color::DarkPurple();
    return COLORS[_teamIdx];
}

void Player::setLevel(int level)
{
    _level = level;
    _model.Unload();
    _model.Load(MODELS[_level - 1]);
}

Player::~Player()
{
}

void Player::draw() const
{
    float yFloatingAnim = _incantating ? sinf(GetTime() * 2.0f) * 0.35f - 0.75f : 0.0f;
    _model.Draw(
        _position + OFFSET - (raylib::Vector3(_mapSize.GetX() / 2, yFloatingAnim, _mapSize.GetY() / 2)),
        {0.0f, 1.0f, 0.0f},
        -90.0f * (_orientation) + 180.0f,
        {0.1f, 0.1f, 0.1f},
        getColor()
    );
}
