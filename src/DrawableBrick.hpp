#pragma once

#include "Brick.hpp"
#include <iostream>

class DrawableBrick : public Brick, public sf::Drawable {
public:
    DrawableBrick() : DrawableBrick({0, 0})
    {
    }

    DrawableBrick(sf::Vector2f win_pos) : in_window_pos(win_pos)
    {
        for (int i = 0; i < 4; i++) {
            bricks[i].setSize(sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1));
            bricks[i].setFillColor(sf::Color::Transparent);
        }
    }

    void set_window_position(sf::Vector2f win_pos) noexcept
    {
        in_window_pos = win_pos;
    }

    // no need this func
    sf::Vector2i get_center_position() const noexcept
    {
        return position[0];
    }

    // no need this func
    void rotate() noexcept
    {
    }

    void set_size(float size_)
    {
        size = size_;
        for (int i = 0; i < 4; i++) {
            bricks[i].setSize(sf::Vector2f(size - 1, size - 1));
        }
    }

    void move(const sf::Vector2i dxdy, bool check_collision = true) noexcept
    {
        sf::Vector2i prev_pos[4];
        write_position(prev_pos);

        for (auto& i : position)
            i += dxdy;
    }

    void setOutlineThickness(float thnickness) noexcept
    {
        for (int i = 0; i < 4; i++) {
            bricks[i].setOutlineThickness(thnickness);
        }
    }

    void setOutlineColor(sf::Color clr) noexcept
    {
        for (int i = 0; i < 4; i++) {
            bricks[i].setOutlineColor(clr);
        }
    }

    void set_color(sf::Color clr) noexcept
    {
        color = clr;
        for (int i = 0; i < 4; i++) {
            bricks[i].setFillColor(color);
        }
    }

    void set_position(const Brick& brick) noexcept
    {
        sf::Vector2i pos[4];
        sf::Vector2i diff;

        brick.write_position(pos);
        if (pos[0].x > 0) {
            diff.x = -pos[0].x;
        }

        for (int i = 0; i < 4; i++) {
            position[i] = pos[i] + diff;
            bricks[i].setPosition(
                    position[i].x * (size) + in_window_pos.x,
                    position[i].y * (size) + in_window_pos.y);
        }
    }

    void set_position(const sf::Vector2i pos[4]) noexcept
    {
        for (int i = 0; i < 4; i++) {
            position[i] = pos[i];
            bricks[i].setPosition(
                    pos[i].x * (size) + in_window_pos.x,
                    pos[i].y * (size) + in_window_pos.y);
        }
    }

    void draw(sf::RenderTarget& target, sf::RenderStates state) const
    {
        for (auto& i : bricks) {
            target.draw(i);
        }
    }

protected:
    sf::RectangleShape bricks[4];
    sf::Vector2f in_window_pos;

    float size = CELL_SIZE;
};