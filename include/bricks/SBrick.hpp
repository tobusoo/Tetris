#pragma once

#include <bricks/Brick.hpp>

class SBrick : public Brick {
public:
    SBrick(sf::Vector2i pos) noexcept;
    sf::Vector2i get_center_position() const noexcept;

    void rotate() noexcept;
};