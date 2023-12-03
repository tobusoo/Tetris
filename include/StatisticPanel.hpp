#pragma once

#include <SFML/Graphics.hpp>

class StatisticPanel : public sf::Drawable {
public:
    StatisticPanel(sf::Vector2f position, sf::Vector2f size);

    void set_lines(size_t n) noexcept;
    void set_score(size_t n) noexcept;
    void increase_i_brick(unsigned short i) noexcept;

    size_t get_lines() const noexcept;
    size_t get_score() const noexcept;
    size_t get_i_brick(unsigned short i) const noexcept;

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates state) const;

private:
    DrawableBrick bricks[BRICKS_N];
    size_t bricks_count[BRICKS_N];
    sf::Text bricks_text[BRICKS_N];

    sf::Font font;
    sf::Text lines_text;
    sf::Text score_text;

    size_t lines;
    size_t score;

    sf::Vector2f panel_position;
    sf::Vector2f panel_size;

    sf::RectangleShape backgroung;
};