#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "Option.hpp"

class Brick {
public:
    virtual ~Brick()
    {
    }

    virtual void rotate() noexcept = 0;

    void write_position(sf::Vector2i prev_array[4])
    {
        for (int i = 0; i < 4; i++) {
            prev_array[i] = position[i];
        }
    }

    void reset_state()
    {
        state = prev_state;
    }

    sf::Vector2i get_leftmost_position() const noexcept
    {
        sf::Vector2i leftmost = {position[0].x, position[0].y};

        for (int i = 1; i < 4; i++) {
            if (position[i].x < leftmost.x) {
                leftmost = position[i];
            }
        }

        return leftmost;
    }

    sf::Vector2i get_rightmost_position() const noexcept
    {
        sf::Vector2i rightmost = {position[0].x, position[0].y};

        for (int i = 1; i < 4; i++) {
            if (position[i].x > rightmost.x) {
                rightmost = position[i];
            }
        }

        return rightmost;
    }

    sf::Vector2i get_highter_position() const noexcept
    {
        sf::Vector2i highter = {position[0].x, position[0].y};

        for (int i = 1; i < 4; i++) {
            if (position[i].y < highter.y) {
                highter = position[i];
            }
        }

        return highter;
    }

    const sf::Color get_color() const
    {
        return color;
    }

    void set_position(sf::Vector2i pos[4])
    {
        for (int i = 0; i < 4; i++)
            position[i] = pos[i];
    }

    bool is_out_of_screen()
    {
        sf::Vector2i leftmost = get_leftmost_position();
        sf::Vector2i rightmost = get_rightmost_position();
        sf::Vector2i highter = get_highter_position();

        if (leftmost.x < 0 || rightmost.x > M - 1 || highter.y < 0) {
            return true;
        }

        return false;
    }

    void move(sf::Vector2i dxdy, bool check_collision = true) noexcept
    {
        sf::Vector2i prev_pos[4];
        write_position(prev_pos);

        for (auto& i : position)
            i += dxdy;

        if (check_collision && is_out_of_screen())
            set_position(prev_pos);
    }

protected:
    sf::Vector2i position[4];
    sf::Color color;
    int state = 0;
    int prev_state = 0;
};