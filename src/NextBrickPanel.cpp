#include <SFML/Graphics.hpp>
#include <iostream>

#include <Bricks.h>
#include <BricksGenerator.hpp>
#include <NextBrickPanel.hpp>

NextBrickPanel::NextBrickPanel(
        sf::Vector2f position, sf::Vector2f size) noexcept
    : background(size)
{
    if (!font.loadFromFile("resource/font.otf")) {
        exit(EXIT_FAILURE);
    }

    background.setPosition(position);
    background.setFillColor(sf::Color::Transparent);
    background.setOutlineThickness(1);
    background.setOutlineColor(sf::Color::White);

    text.setFont(font);
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(30);
    text.setPosition(position + sf::Vector2f(20, 0));
    text.setString("NEXT");

    next_brick.set_size(25);
    next_brick.set_window_position(position + sf::Vector2f(10, 40));
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
