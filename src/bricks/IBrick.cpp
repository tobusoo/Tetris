#include <bricks/IBrick.hpp>

IBrick::IBrick(sf::Vector2i pos) noexcept
{
    color = sf::Color::Blue;
    for (int i = 0; i < 4; i++) {
        position[i] = sf::Vector2i(pos.x + i, pos.y);
    }
}

sf::Vector2i IBrick::get_center_position() const noexcept
{
    return position[1];
}

void IBrick::right_rotate() noexcept
{
    if (state == 0) {
        state = 1;
        prev_state = 0;

        position[0] += sf::Vector2i(1, -1);
        // position[1] += sf::Vector2i(0, 0);
        position[2] += sf::Vector2i(-1, 1);
        position[3] += sf::Vector2i(-2, 2);
    } else if (state == 1) {
        state = 0;
        prev_state = 1;

        position[0] += sf::Vector2i(-1, 1);
        // position[1] += sf::Vector2i(0, 0);
        position[2] += sf::Vector2i(1, -1);
        position[3] += sf::Vector2i(2, -2);
    }
}

void IBrick::left_rotate() noexcept
{
}

void IBrick::rotate(bool is_right) noexcept
{
    if (is_right)
        right_rotate();
    else
        left_rotate();
}
