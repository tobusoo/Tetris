#pragma once

#include "Brick.hpp"
#include <iostream>

class IBrick : public Brick {
public:
    IBrick(sf::Vector2i pos)
    {
        color = sf::Color::Blue;
        for (int i = 0; i < 4; i++) {
            position[i] = sf::Vector2i(pos.x, pos.y + i);
        }
    }

    void rotate() noexcept
    {
    }
};