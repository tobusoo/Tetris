#pragma once

#include <bricks/Brick.hpp>

class OBrick : public Brick {
public:
    OBrick(sf::Vector2i pos) noexcept;
    // actualy this function is no need
    sf::Vector2i get_center_position() const noexcept;

    void rotate(bool is_right = true) noexcept;

protected:
    void right_rotate() noexcept;
    void left_rotate() noexcept;
};