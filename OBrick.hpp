#pragma once

#include "Brick.hpp"
#include <iostream>

class OBrick : public Brick {
public:
    OBrick(sf::Vector2i pos)
    {
        color = sf::Color::Yellow;
        position[0] = sf::Vector2i(pos.x, pos.y);
        position[1] = sf::Vector2i(pos.x + 1, pos.y);
        position[2] = sf::Vector2i(pos.x, pos.y + 1);
        position[3] = sf::Vector2i(pos.x + 1, pos.y + 1);
    }

    void rotate() noexcept
    {
    }
};