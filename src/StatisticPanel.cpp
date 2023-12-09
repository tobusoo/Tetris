#include <SFML/Graphics.hpp>

#include <Bricks.h>
#include <BricksGenerator.hpp>
#include <StatisticPanel.hpp>

StatisticPanel::StatisticPanel(sf::Vector2f position)
    : lines(0),
      score(0),
      panel_position(position),
      background({200, CELL_SIZE * N + 1})
{
    if (!font.loadFromFile("resource/font.otf")) {
        exit(EXIT_FAILURE);
    }

    background.setFillColor(sf::Color::Transparent);
    background.setOutlineColor(sf::Color(224, 224, 224, 255 / 2));
    background.setOutlineThickness(3);
    background.setPosition(position);

    lines_text.setFont(font);
    lines_text.setFillColor(sf::Color::White);
    lines_text.setCharacterSize(24);
    lines_text.setPosition(position + sf::Vector2f(0, 0));
    lines_text.setString("Lines: 0");

    score_text.setFont(font);
    score_text.setFillColor(sf::Color::White);
    score_text.setCharacterSize(24);
    score_text.setPosition(position + sf::Vector2f(0, 30));
    score_text.setString("Score: 0");

    BricksGenerator generator;
    Brick* brick = nullptr;
    for (int i = 0; i < BRICKS_N; i++) {
        brick = generator.get_i_brick(i);
        bricks_count[i] = 0;

        bricks[i].set_window_position(
                sf::Vector2f(position.x + 10, position.y + i * 80 + 70));
        bricks[i].set_size(25);
        bricks[i].set_color(brick->get_color());
        bricks[i].set_position(*brick);

        bricks_text[i].setFont(font);
        bricks_text[i].setFillColor(sf::Color::White);
        bricks_text[i].setCharacterSize(24);
        bricks_text[i].setPosition(
                sf::Vector2f(position.x + 120, position.y + i * 80 + 70));
        bricks_text[i].setString("0");

        delete brick;
    }
}

void StatisticPanel::set_lines(size_t n) noexcept
{
    lines = n;
    lines_text.setString("Lines: " + std::to_string(lines));
}

size_t StatisticPanel::get_lines() const noexcept
{
    return lines;
}

size_t StatisticPanel::get_score() const noexcept
{
    return score;
}

void StatisticPanel::set_score(size_t n) noexcept
{
    score = n;
    score_text.setString("Score: " + std::to_string(score));
}

void StatisticPanel::increase_i_brick(unsigned short i) noexcept
{
    if (i >= BRICKS_N)
        return;
    bricks_text[i].setString(std::to_string(++bricks_count[i]));
}

size_t StatisticPanel::get_i_brick(unsigned short i) const noexcept
{
    if (i >= BRICKS_N)
        return bricks_count[0];

    return bricks_count[i];
}

void StatisticPanel::reset() noexcept
{
    lines = 0;
    score = 0;
    for (int i = 0; i < BRICKS_N; i++) {
        bricks_count[i] = 0;
        bricks_text[i].setString("0");
    }

    set_lines(lines);
    set_score(score);
}

void StatisticPanel::draw(
        sf::RenderTarget& target, sf::RenderStates state) const
{
    target.draw(background, state);
    target.draw(lines_text, state);
    target.draw(score_text, state);

    for (int i = 0; i < BRICKS_N; i++) {
        target.draw(bricks[i]);
        target.draw(bricks_text[i]);
    }
}
