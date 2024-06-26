#pragma once

#include <SFML/Graphics.hpp>

#include <Option.hpp>

class Brick {
public:
    Brick() = default;

    void write_position(sf::Vector2i prev_pos[4]) const noexcept;
    void set_color(sf::Color clr) noexcept;
    void set_position(const sf::Vector2i pos[4]) noexcept;

    virtual sf::Vector2i get_center_position() const noexcept = 0;
    sf::Vector2i get_leftmost_position() const noexcept;
    sf::Vector2i get_rightmost_position() const noexcept;
    sf::Vector2i get_highest_position() const noexcept;
    sf::Vector2i get_lower_position() const noexcept;
    sf::Color get_color() const noexcept;

    bool is_out_of_screen() const noexcept;
    bool is_out_of_screen(
            sf::Vector2i& leftmost, sf::Vector2i& rightmost) const noexcept;

    virtual void rotate(bool is_right = true) noexcept = 0;
    void reset_state() noexcept;
    void move(const sf::Vector2i dxdy, bool check_collision = true) noexcept;

    virtual ~Brick() = default;

protected:
    virtual void right_rotate() noexcept = 0;
    virtual void left_rotate() noexcept = 0;

    sf::Vector2i position[4];
    sf::Color color;
    int state = 0;
    int prev_state = 0;
};