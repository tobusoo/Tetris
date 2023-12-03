#pragma once

#include <bricks/Brick.hpp>

class TBrick : public Brick {
public:
    TBrick(sf::Vector2i pos) noexcept;
    sf::Vector2i get_center_position() const noexcept;

    void rotate() noexcept;
};