#pragma once

#include <bricks/Brick.hpp>

class IBrick : public Brick {
public:
    IBrick(sf::Vector2i pos) noexcept;
    sf::Vector2i get_center_position() const noexcept;

    void rotate() noexcept;
};