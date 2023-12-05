#pragma once
#include <bricks/Brick.hpp>

class ZBrick : public Brick {
public:
    ZBrick(sf::Vector2i pos) noexcept;
    sf::Vector2i get_center_position() const noexcept;

    void rotate(bool is_right = true) noexcept;

protected:
    void right_rotate() noexcept;
    void left_rotate() noexcept;
};