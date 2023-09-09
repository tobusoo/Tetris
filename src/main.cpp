#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <vector>

#include "Bricks.h"
#include "BricksGenerator.hpp"
#include "Field.hpp"
#include "NextBrickPanel.hpp"
#include "Option.hpp"
#include "StatisticPanel.hpp"

int main()
{
    sf::VideoMode vmode(WINDOW_WIDTH, WINDOW_HEIGTH);
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(vmode, "Tetris", sf::Style::Resize, settings);
    window.setPosition(sf::Vector2i(200, 0));
    window.setFramerateLimit(144);
    sf::Event event;

    Field field(sf::Vector2f(
            WINDOW_WIDTH / 2 - CELL_SIZE * M / 2,
            WINDOW_HEIGTH / 2 - CELL_SIZE * M));
    StatisticPanel stat_panel(
            sf::Vector2f(WINDOW_WIDTH / 12, WINDOW_HEIGTH / 12),
            sf::Vector2f(200, 400));
    NextBrickPanel next_panel(sf::Vector2f(600, 50), sf::Vector2f(150, 150));
    BricksGenerator generator;

    Brick* brick = generator.get_random_brick();
    brick->move(sf::Vector2i(3, 0));
    field.set_brick(*brick, true);
    stat_panel.increase_i_count(generator.get_last_i());

    Brick* next_brick = generator.get_random_brick();

    sf::Vector2i movement;
    bool rotate_key = false;
    bool fast_down = false;

    next_panel.set_brick_color(next_brick->get_color());
    next_panel.set_brick(*next_brick);

    sf::Clock time;
    float dt;
    while (window.isOpen()) {
        dt = time.getElapsedTime().asSeconds();
        time.restart();

        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
                if (event.key.code == sf::Keyboard::Down)
                    movement.y = 1;
                if (event.key.code == sf::Keyboard::Left)
                    movement.x = -1;
                if (event.key.code == sf::Keyboard::Right)
                    movement.x = 1;
                if (event.key.code == sf::Keyboard::Space)
                    rotate_key = true;
                if (event.key.code == sf::Keyboard::Up)
                    fast_down = true;
            default:
                break;
            }
        }

        field.update((*brick), movement, dt, rotate_key, fast_down);
        movement = {0, 0};
        rotate_key = false;
        fast_down = false;

        if (field.collide(*brick) && field.need_new_brick()) {
            stat_panel.increase_i_count(generator.get_last_i());
            field.set_brick(*brick);
            field.reset_time();
            delete brick;

            brick = next_brick;
            brick->move(sf::Vector2i(3, 0));
            next_brick = generator.get_random_brick();

            next_panel.set_brick_color(next_brick->get_color());
            next_panel.set_brick(*next_brick);
        }

        field.check_lines();

        {
            auto cur_lines = field.get_lines();
            auto cur_score = field.get_score();

            if (cur_lines > stat_panel.get_lines()) {
                stat_panel.set_lines(cur_lines);
                stat_panel.set_score(cur_score);
            }
        }

        window.clear();
        window.draw(field);
        window.draw(next_panel);
        window.draw(stat_panel);
        window.display();

        if (field.end()) {
            delete next_brick;
            delete brick;
            window.close();
        }
    }

    std::cout << "Your score: " << stat_panel.get_score() << '\n';
    std::cout << "Your Lines: " << stat_panel.get_lines() << '\n';

    return 0;
}