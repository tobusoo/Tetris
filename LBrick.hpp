#pragma once

#include "Brick.hpp"
#include <iostream>

class LBrick : public Brick {
public:
    LBrick(sf::Vector2i pos)
    {
        color = sf::Color(204, 102, 0);
        position[0] = sf::Vector2i(pos.x, pos.y + 1);
        position[1] = sf::Vector2i(pos.x + 1, pos.y + 1);
        position[2] = sf::Vector2i(pos.x + 2, pos.y + 1);
        position[3] = sf::Vector2i(pos.x + 2, pos.y);
    }

    void rotate() noexcept
    {
    }
};