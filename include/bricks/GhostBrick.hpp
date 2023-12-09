#pragma once

#include <bricks/DrawableBrick.hpp>

class GhostBrick : public DrawableBrick {
public:
    GhostBrick(sf::Vector2f win_pos);
    void set_bricks_position();

private:
    const float padding = 5;
};