#pragma once

#include "Brick.hpp"
#include <iostream>

class SBrick : public Brick {
public:
    SBrick(sf::Vector2i pos)
    {
        color = sf::Color::Green;
        position[0] = sf::Vector2i(pos.x, pos.y + 1);
        position[1] = sf::Vector2i(pos.x + 1, pos.y + 1);
        position[2] = sf::Vector2i(pos.x + 1, pos.y);
        position[3] = sf::Vector2i(pos.x + 2, pos.y);
    }

    void rotate() noexcept
    {
    }
};