#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include <Option.hpp>

class Brick {
public:
    virtual ~Brick() = default;

    void write_position(sf::Vector2i prev_array[4]) const noexcept;
    void set_color(sf::Color clr) noexcept;
    void set_position(const sf::Vector2i pos[4]) noexcept;

    virtual sf::Vector2i get_center_position() const noexcept = 0;
    sf::Vector2i get_leftmost_position() const noexcept;
    sf::Vector2i get_rightmost_position() const noexcept;
    sf::Vector2i get_highter_position() const noexcept;
    sf::Vector2i get_lower_position() const noexcept;
    const sf::Color get_color() const noexcept;

    bool is_out_of_screen() const noexcept;
    bool is_out_of_screen(
            sf::Vector2i& leftmost, sf::Vector2i& rightmost) const noexcept;

    virtual void rotate() noexcept = 0;
    void reset_state() noexcept;
    void move(const sf::Vector2i dxdy, bool check_collision = true) noexcept;

protected:
    sf::Vector2i position[4];
    sf::Color color;
    int state = 0;
    int prev_state = 0;
};