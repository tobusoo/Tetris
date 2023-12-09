#include <SFML/Graphics.hpp>

#include <Bricks.h>
#include <BricksGenerator.hpp>
#include <NextBrickPanel.hpp>

NextBrickPanel::NextBrickPanel(sf::Vector2f position) noexcept
    : background({200, 150})
{
    if (!font.loadFromFile("resource/font.otf")) {
        exit(EXIT_FAILURE);
    }

    background.setPosition(position);
    background.setFillColor(sf::Color::Transparent);
    background.setOutlineThickness(3);
    background.setOutlineColor(sf::Color(224, 224, 224, 255 / 2));

    text.setFont(font);
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(30);
    text.setPosition(position + sf::Vector2f(200 / 2 - 30, 0));
    text.setString("NEXT");

    next_brick.set_size(CELL_SIZE);
    next_brick.set_window_position(position + sf::Vector2f(60, 60));
}

void NextBrickPanel::set_brick(Brick& brick) noexcept
{
    next_brick.set_position(brick);
    next_brick.set_color(brick.get_color());
}

void NextBrickPanel::draw(
        sf::RenderTarget& target, sf::RenderStates state) const
{
    target.draw(background, state);
    target.draw(text, state);
    target.draw(next_brick, state);
}
