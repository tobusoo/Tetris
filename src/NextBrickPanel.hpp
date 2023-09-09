#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Bricks.h"
#include "BricksGenerator.hpp"

class NextBrickPanel : public sf::Drawable {
public:
    NextBrickPanel(sf::Vector2f position, sf::Vector2f size) noexcept
        : background(size)
    {
        if (!font.loadFromFile("resource/font.otf")) {
            exit(EXIT_FAILURE);
        }

        background.setPosition(position);
        background.setFillColor(sf::Color::Transparent);
        background.setOutlineThickness(1);
        background.setOutlineColor(sf::Color::White);

        text_next.setFont(font);
        text_next.setFillColor(sf::Color::White);
        text_next.setCharacterSize(30);
        text_next.setPosition(position + sf::Vector2f(20, 0));
        text_next.setString("NEXT");

        next_brick.set_size(25);
        next_brick.set_window_position(position + sf::Vector2f(10, 40));
    }

    void set_brick_color(sf::Color color) noexcept
    {
        next_brick.set_color(color);
    }

    void set_brick(Brick& brick) noexcept
    {
        next_brick.set_position(brick);
    }

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates state) const
    {
        target.draw(background);
        target.draw(text_next);
        target.draw(next_brick);
    }

private:
    DrawableBrick next_brick;

    sf::Font font;
    sf::Text text_next;

    sf::RectangleShape background;
};