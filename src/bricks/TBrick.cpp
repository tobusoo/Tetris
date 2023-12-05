#include <bricks/TBrick.hpp>

TBrick::TBrick(sf::Vector2i pos) noexcept
{
    color = sf::Color(76, 0, 153);
    position[0] = sf::Vector2i(pos.x, pos.y + 1);
    position[1] = sf::Vector2i(pos.x + 1, pos.y + 1);
    position[2] = sf::Vector2i(pos.x + 1, pos.y);
    position[3] = sf::Vector2i(pos.x + 2, pos.y + 1);
}

sf::Vector2i TBrick::get_center_position() const noexcept
{
    return position[1];
}

void TBrick::right_rotate() noexcept
{
    switch (state) {
    case 0:
        position[0] += sf::Vector2i(1, -1);
        // position[1] += sf::Vector2i(0, 0);
        position[2] += sf::Vector2i(1, 1);
        position[3] += sf::Vector2i(-1, 1);

        prev_state = state;
        state++;
        break;
    case 1:
        position[0] += sf::Vector2i(1, 1);
        // position[1] += sf::Vector2i(0, 0);
        position[2] += sf::Vector2i(-1, 1);
        position[3] += sf::Vector2i(-1, -1);

        prev_state = state;
        state++;
        break;
    case 2:
        position[0] += sf::Vector2i(-1, 1);
        // position[1] += sf::Vector2i(0, 0);
        position[2] += sf::Vector2i(-1, -1);
        position[3] += sf::Vector2i(1, -1);

        prev_state = state;
        state++;
        break;
    case 3:
        position[0] += sf::Vector2i(-1, -1);
        // position[1] += sf::Vector2i(0, 0);
        position[2] += sf::Vector2i(1, -1);
        position[3] += sf::Vector2i(1, 1);

        prev_state = state;
        state = 0;
        break;
    default:
        break;
    }
}

void TBrick::left_rotate() noexcept
{
}

void TBrick::rotate(bool is_right) noexcept
{
    if (is_right)
        right_rotate();
    else
        left_rotate();
}