#include <bricks/GhostBrick.hpp>

GhostBrick::GhostBrick(sf::Vector2f win_pos) : DrawableBrick(win_pos)
{
    for (int i = 0; i < 4; i++) {
        bricks[i].setSize(
                sf::Vector2f(CELL_SIZE - padding, CELL_SIZE - padding));
        bricks[i].setOutlineThickness(1);
        bricks[i].setOutlineColor(color);
        bricks[i].setFillColor(sf::Color::Transparent);
    }
}

void GhostBrick::set_bricks_position()
{
    for (int i = 0; i < 4; i++) {
        auto pos = position[i];
        bricks[i].setPosition(
                pos.x * CELL_SIZE + in_window_pos.x + padding / 2,
                pos.y * CELL_SIZE + in_window_pos.y + padding / 2);
    }
}
