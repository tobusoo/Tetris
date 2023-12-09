#pragma once

#include <bricks/Brick.hpp>

class DrawableBrick : public Brick, public sf::Drawable {
public:
    DrawableBrick();
    DrawableBrick(sf::Vector2f win_pos);

    void set_window_position(sf::Vector2f win_pos) noexcept;
    void set_color(sf::Color clr) noexcept;
    void set_position(const Brick& brick) noexcept;
    void set_position(const sf::Vector2i pos[4]) noexcept;
    void setOutlineThickness(float thickness) noexcept;
    void setOutlineColor(sf::Color clr) noexcept;
    void set_size(float size_) noexcept;

    sf::Vector2i get_center_position() const noexcept;

    void rotate(bool is_right = true) noexcept;
    void move(const sf::Vector2i dxdy) noexcept;

    void draw(sf::RenderTarget& target, sf::RenderStates state) const;

protected:
    void right_rotate() noexcept;
    void left_rotate() noexcept;

    sf::RectangleShape bricks[4];
    sf::Vector2f in_window_pos;

    float size = CELL_SIZE;
};