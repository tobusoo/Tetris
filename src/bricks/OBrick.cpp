#include <bricks/OBrick.hpp>

OBrick::OBrick(sf::Vector2i pos) noexcept
{
    color = sf::Color(255, 255, 204);
    position[0] = sf::Vector2i(pos.x, pos.y);
    position[1] = sf::Vector2i(pos.x + 1, pos.y);
    position[2] = sf::Vector2i(pos.x, pos.y + 1);
    position[3] = sf::Vector2i(pos.x + 1, pos.y + 1);
}

// actualy this function is no need
sf::Vector2i OBrick::get_center_position() const noexcept
{
    return position[0];
}

void OBrick::right_rotate() noexcept
{
    // No need to rotate, because it's square.
}

void OBrick::left_rotate() noexcept
{
    // No need to rotate, because it's square.
}

void OBrick::rotate(bool is_right) noexcept
{
    // No need to rotate, because it's square.
    if (is_right)
        return;
}
