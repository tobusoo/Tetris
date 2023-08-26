#pragma once

#include "Brick.hpp"
#include <iostream>

class JBrick : public Brick {
public:
    JBrick(sf::Vector2i pos)
    {
        color = sf::Color(0, 0, 102);
        position[0] = sf::Vector2i(pos.x, pos.y);
        position[1] = sf::Vector2i(pos.x, pos.y + 1);
        position[2] = sf::Vector2i(pos.x + 1, pos.y + 1);
        position[3] = sf::Vector2i(pos.x + 2, pos.y + 1);
    }

    void rotate() noexcept
    {
    }
};