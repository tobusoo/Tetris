#pragma once

#include "Brick.hpp"
#include <iostream>

class IBrick : public Brick {
public:
    IBrick(sf::Vector2i pos) noexcept
    {
        color = sf::Color::Blue;
        for (int i = 0; i < 4; i++) {
            position[i] = sf::Vector2i(pos.x + i, pos.y);
        }
    }

    sf::Vector2i get_center_position() const noexcept
    {
        return position[1];
    }

    // TODO: Add 2 more states
    void rotate() noexcept
    {
        if (state == 0) {
            state = 1;
            prev_state = 0;

            position[0] += sf::Vector2i(1, -1);
            // position[1] += sf::Vector2i(0, 0);
            position[2] += sf::Vector2i(-1, 1);
            position[3] += sf::Vector2i(-2, 2);
        } else if (state == 1) {
            state = 0;
            prev_state = 1;

            position[0] += sf::Vector2i(-1, 1);
            // position[1] += sf::Vector2i(0, 0);
            position[2] += sf::Vector2i(1, -1);
            position[3] += sf::Vector2i(2, -2);
        }
    }
};