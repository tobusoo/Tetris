#pragma once

#include "Brick.hpp"
#include <iostream>

class GhostBrick : public DrawableBrick {
public:
    GhostBrick(sf::Vector2f win_pos) : DrawableBrick(win_pos)
    {
        for (int i = 0; i < 4; i++) {
            bricks[i].setSize(
                    sf::Vector2f(CELL_SIZE - distance, CELL_SIZE - distance));
            bricks[i].setOutlineThickness(1);
            bricks[i].setOutlineColor(color);
            bricks[i].setFillColor(sf::Color::Transparent);
        }
    }

    void set_bricks_position()
    {
        for (int i = 0; i < 4; i++) {
            auto pos = position[i];
            bricks[i].setPosition(
                    pos.x * CELL_SIZE + in_window_pos.x + distance / 2,
                    pos.y * CELL_SIZE + in_window_pos.y + distance / 2);
        }
    }

    void draw(sf::RenderTarget& target, sf::RenderStates state) const
    {
        for (auto& i : bricks) {
            target.draw(i);
        }
    }

private:
    const float distance = 5;
};