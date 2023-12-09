#include <bricks/ZBrick.hpp>

ZBrick::ZBrick(sf::Vector2i pos) noexcept
{
    color = sf::Color::Red;
    position[0] = sf::Vector2i(pos.x, pos.y);
    position[1] = sf::Vector2i(pos.x + 1, pos.y);
    position[2] = sf::Vector2i(pos.x + 1, pos.y + 1);
    position[3] = sf::Vector2i(pos.x + 2, pos.y + 1);
}

sf::Vector2i ZBrick::get_center_position() const noexcept
{
    return position[2];
}

void ZBrick::right_rotate() noexcept
{
    switch (state) {
    case 0:
        position[0] += sf::Vector2i(2, 0);
        position[1] += sf::Vector2i(1, 1);
        // position[2] += sf::Vector2i(0, 0);
        position[3] += sf::Vector2i(-1, 1);

        prev_state = state;
        state++;
        break;
    case 1:
        position[0] += sf::Vector2i(0, 2);
        position[1] += sf::Vector2i(-1, 1);
        // position[2] += sf::Vector2i(0, 0);
        position[3] += sf::Vector2i(-1, -1);

        prev_state = state;
        state++;
        break;
    case 2:
        position[0] += sf::Vector2i(-2, 0);
        position[1] += sf::Vector2i(-1, -1);
        // position[2] += sf::Vector2i(0, 0);
        position[3] += sf::Vector2i(1, -1);

        prev_state = state;
        state++;
        break;
    case 3:
        position[0] += sf::Vector2i(0, -2);
        position[1] += sf::Vector2i(1, -1);
        // position[2] += sf::Vector2i(0, 0);
        position[3] += sf::Vector2i(1, 1);

        prev_state = state;
        state = 0;
        break;
    default:
        break;
    }
}

void ZBrick::left_rotate() noexcept
{
    switch (state) {
    case 0:
        position[0] += sf::Vector2i(0, 2);
        position[1] += sf::Vector2i(-1, 1);
        // position[2] += sf::Vector2i(0, 0);
        position[3] += sf::Vector2i(-1, -1);

        prev_state = state;
        state = 3;
        break;
    case 1:
        position[0] += sf::Vector2i(-2, 0);
        position[1] += sf::Vector2i(-1, -1);
        // position[2] += sf::Vector2i(0, 0);
        position[3] += sf::Vector2i(1, -1);

        prev_state = state;
        state = 0;
        break;
    case 2:
        position[0] += sf::Vector2i(0, -2);
        position[1] += sf::Vector2i(1, -1);
        // position[2] += sf::Vector2i(0, 0);
        position[3] += sf::Vector2i(1, 1);

        prev_state = state;
        state = 1;
        break;
    case 3:
        position[0] += sf::Vector2i(2, 0);
        position[1] += sf::Vector2i(1, 1);
        // position[2] += sf::Vector2i(0, 0);
        position[3] += sf::Vector2i(-1, 1);

        prev_state = state;
        state = 2;
        break;
    default:
        break;
    }
}

void ZBrick::rotate(bool is_right) noexcept
{
    if (is_right)
        right_rotate();
    else
        left_rotate();
}