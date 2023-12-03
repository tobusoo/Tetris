#include <bricks/SBrick.hpp>

SBrick::SBrick(sf::Vector2i pos) noexcept
{
    color = sf::Color::Green;
    position[0] = sf::Vector2i(pos.x, pos.y + 1);
    position[1] = sf::Vector2i(pos.x + 1, pos.y + 1);
    position[2] = sf::Vector2i(pos.x + 1, pos.y);
    position[3] = sf::Vector2i(pos.x + 2, pos.y);
}

sf::Vector2i SBrick::get_center_position() const noexcept
{
    return position[1];
}

void SBrick::rotate() noexcept
{
    switch (state) {
    case 0:
        position[0] += sf::Vector2i(1, -1);
        // position[1] += sf::Vector2i(0, 0);
        position[2] += sf::Vector2i(1, 1);
        position[3] += sf::Vector2i(0, 2);

        prev_state = state;
        state++;
        break;
    case 1:
        position[0] += sf::Vector2i(1, 1);
        // position[1] += sf::Vector2i(0, 0);
        position[2] += sf::Vector2i(-1, 1);
        position[3] += sf::Vector2i(-2, 0);

        prev_state = state;
        state++;
        break;
    case 2:
        position[0] += sf::Vector2i(-1, 1);
        // position[1] += sf::Vector2i(0, 0);
        position[2] += sf::Vector2i(-1, -1);
        position[3] += sf::Vector2i(0, -2);

        prev_state = state;
        state++;
        break;
    case 3:
        position[0] += sf::Vector2i(-1, -1);
        // position[1] += sf::Vector2i(0, 0);
        position[2] += sf::Vector2i(1, -1);
        position[3] += sf::Vector2i(2, 0);

        prev_state = state;
        state = 0;
        break;
    default:
        break;
    }
}