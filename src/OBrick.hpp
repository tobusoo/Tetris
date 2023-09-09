#pragma once

#include "Brick.hpp"
#include <iostream>

class OBrick : public Brick {
public:
    OBrick(sf::Vector2i pos) noexcept
    {
        color = sf::Color(255, 255, 204);
        position[0] = sf::Vector2i(pos.x, pos.y);
        position[1] = sf::Vector2i(pos.x + 1, pos.y);
        position[2] = sf::Vector2i(pos.x, pos.y + 1);
        position[3] = sf::Vector2i(pos.x + 1, pos.y + 1);
    }

    // actualy this function is no need
    sf::Vector2i get_center_position() const noexcept
    {
        return position[0];
    }

    void rotate() noexcept
    {
        // No need to rotate, because it's square.
    }
};