#include <SFML/Graphics.hpp>
#include <vector>

#include <Bricks.h>
#include <Option.hpp>

void Brick::write_position(sf::Vector2i prev_array[4]) const noexcept
{
    for (int i = 0; i < 4; i++) {
        prev_array[i] = position[i];
    }
}

void Brick::reset_state() noexcept
{
    state = prev_state;
}

sf::Vector2i Brick::get_leftmost_position() const noexcept
{
    sf::Vector2i leftmost = {position[0].x, position[0].y};

    for (int i = 1; i < 4; i++) {
        if (position[i].x < leftmost.x) {
            leftmost = position[i];
        }
    }

    return leftmost;
}

sf::Vector2i Brick::get_rightmost_position() const noexcept
{
    sf::Vector2i rightmost = {position[0].x, position[0].y};

    for (int i = 1; i < 4; i++) {
        if (position[i].x > rightmost.x) {
            rightmost = position[i];
        }
    }

    return rightmost;
}

sf::Vector2i Brick::get_highter_position() const noexcept
{
    sf::Vector2i highter = {position[0].x, position[0].y};

    for (int i = 1; i < 4; i++) {
        if (position[i].y < highter.y) {
            highter = position[i];
        }
    }

    return highter;
}

sf::Vector2i Brick::get_lower_position() const noexcept
{
    sf::Vector2i lower = {position[0].x, position[0].y};

    for (int i = 1; i < 4; i++) {
        if (position[i].y > lower.y)
            lower = position[i];
    }

    return lower;
}

void Brick::set_color(sf::Color clr) noexcept
{
    color = clr;
}

const sf::Color Brick::get_color() const noexcept
{
    return color;
}

void Brick::set_position(const sf::Vector2i pos[4]) noexcept
{
    for (int i = 0; i < 4; i++)
        position[i] = pos[i];
}

bool Brick::is_out_of_screen(
        sf::Vector2i& leftmost, sf::Vector2i& rightmost) const noexcept
{
    sf::Vector2i highter = get_highter_position();
    leftmost = get_leftmost_position();
    rightmost = get_rightmost_position();

    if (leftmost.x < 0 || rightmost.x > M - 1 || highter.y < 0) {
        return true;
    }

    return false;
}

bool Brick::is_out_of_screen() const noexcept
{
    sf::Vector2i leftmost = get_leftmost_position();
    sf::Vector2i rightmost = get_rightmost_position();
    sf::Vector2i highter = get_highter_position();

    if (leftmost.x < 0 || rightmost.x > M - 1 || highter.y < 0) {
        return true;
    }

    return false;
}

void Brick::move(const sf::Vector2i dxdy, bool check_collision) noexcept
{
    sf::Vector2i prev_pos[4];
    write_position(prev_pos);

    for (auto& i : position)
        i += dxdy;

    if (check_collision && is_out_of_screen())
        set_position(prev_pos);
}
