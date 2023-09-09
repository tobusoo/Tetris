#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Bricks.h"
#include "BricksGenerator.hpp"

class StatisticPanel : public sf::Drawable {
public:
    StatisticPanel(sf::Vector2f position, sf::Vector2f size)
        : lines(0),
          score(0),
          panel_position(position),
          panel_size(size),
          backgroung(size)
    {
        if (!font.loadFromFile("resource/font.otf")) {
            std::cout << "Can't load resource/font.otf";
            exit(EXIT_FAILURE);
        }

        backgroung.setFillColor(sf::Color::Transparent);
        backgroung.setOutlineColor(sf::Color::White);
        backgroung.setOutlineThickness(1);
        backgroung.setPosition(position);

        lines_text.setFont(font);
        lines_text.setFillColor(sf::Color::White);
        lines_text.setCharacterSize(30);
        lines_text.setPosition(position + sf::Vector2f(0, 0));
        lines_text.setString("Lines: 0");

        score_text.setFont(font);
        score_text.setFillColor(sf::Color::White);
        score_text.setCharacterSize(30);
        score_text.setPosition(position + sf::Vector2f(0, 30));
        score_text.setString("Score: 0");

        BricksGenerator generator;
        Brick* brick = nullptr;
        for (int i = 0; i < BRICKS_N; i++) {
            brick = generator.get_i_brick(i);
            bricks_count[i] = 0;

            bricks[i].set_window_position(
                    sf::Vector2f(position.x, position.y + i * 50 + 70));
            bricks[i].set_size(15);
            bricks[i].set_color(brick->get_color());
            bricks[i].set_position(*brick);

            brick_text[i].setFont(font);
            brick_text[i].setFillColor(sf::Color::White);
            brick_text[i].setCharacterSize(15);
            brick_text[i].setPosition(
                    sf::Vector2f(position.x + 65, position.y + i * 50 + 70));
            brick_text[i].setString("0");

            delete brick;
        }
    }

    void set_lines(size_t n) noexcept
    {
        lines = n;
        lines_text.setString("Lines: " + std::to_string(lines));
    }

    size_t get_lines() const noexcept
    {
        return lines;
    }

    size_t get_score() const noexcept
    {
        return score;
    }

    void set_score(size_t n) noexcept
    {
        score = n;
        score_text.setString("Score: " + std::to_string(score));
    }

    void increase_i_count(unsigned short i) noexcept
    {
        if (i >= BRICKS_N)
            return;
        brick_text[i].setString(std::to_string(++bricks_count[i]));
    }

    size_t get_i_count(unsigned short i) const noexcept
    {
        if (i >= BRICKS_N)
            return bricks_count[0];

        return bricks_count[i];
    }

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates state) const
    {
        target.draw(backgroung);
        target.draw(lines_text);
        target.draw(score_text);

        for (int i = 0; i < BRICKS_N; i++) {
            target.draw(bricks[i]);
            target.draw(brick_text[i]);
        }
    }

private:
    DrawableBrick bricks[BRICKS_N];
    size_t bricks_count[BRICKS_N];
    sf::Text brick_text[BRICKS_N];

    sf::Font font;
    sf::Text lines_text;
    sf::Text score_text;

    size_t lines;
    size_t score;

    sf::Vector2f panel_position;
    sf::Vector2f panel_size;

    sf::RectangleShape backgroung;
};