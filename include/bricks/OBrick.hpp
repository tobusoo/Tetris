#pragma once

#include <bricks/Brick.hpp>

class OBrick : public Brick {
public:
    OBrick(sf::Vector2i pos) noexcept;
    // actualy this function is no need
    sf::Vector2i get_center_position() const noexcept;

    void rotate() noexcept;
};