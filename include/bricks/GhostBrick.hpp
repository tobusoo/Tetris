#pragma once

#include <bricks/DrawableBrick.hpp>
#include <iostream>

class GhostBrick : public DrawableBrick {
public:
    GhostBrick(sf::Vector2f win_pos);
    void set_bricks_position();
    void draw(sf::RenderTarget& target, sf::RenderStates state) const;

private:
    const float padding = 5;
};