#include <bricks/LBrick.hpp>

LBrick::LBrick(sf::Vector2i pos) noexcept
{
    color = sf::Color(204, 102, 0);
    position[0] = sf::Vector2i(pos.x, pos.y + 1);
    position[1] = sf::Vector2i(pos.x + 1, pos.y + 1);
    position[2] = sf::Vector2i(pos.x + 2, pos.y + 1);
    position[3] = sf::Vector2i(pos.x + 2, pos.y);
}

sf::Vector2i LBrick::get_center_position() const noexcept
{
    return position[1];
}

void LBrick::right_rotate() noexcept
{
    switch (state) {
    case 0:
        position[0] += sf::Vector2i(1, -1);
        // position[1] += sf::Vector2i(0, 0);
        position[2] += sf::Vector2i(-1, 1);
        position[3] += sf::Vector2i(0, 2);

        prev_state = state;
        state++;
        break;
    case 1:
        position[0] += sf::Vector2i(1, 1);
        // position[1] += sf::Vector2i(0, 0);
        position[2] += sf::Vector2i(-1, -1);
        position[3] += sf::Vector2i(-2, 0);

        prev_state = state;
        state++;
        break;
    case 2:
        position[0] += sf::Vector2i(-1, 1);
        // position[1] += sf::Vector2i(0, 0);
        position[2] += sf::Vector2i(1, -1);
        position[3] += sf::Vector2i(0, -2);

        prev_state = state;
        state++;
        break;
    case 3:
        position[0] += sf::Vector2i(-1, -1);
        // position[1] += sf::Vector2i(0, 0);
        position[2] += sf::Vector2i(1, 1);
        position[3] += sf::Vector2i(2, 0);

        prev_state = state;
        state = 0;
        break;
    default:
        break;
    }
}

void LBrick::left_rotate() noexcept
{
}

void LBrick::rotate(bool is_right) noexcept
{
    if (is_right)
        right_rotate();
    else
        left_rotate();
}
