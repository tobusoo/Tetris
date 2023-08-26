#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "Bricks.h"
#include "Field.hpp"
#include "Option.hpp"

int main()
{
    srand(time(0));
    sf::VideoMode vmode(WINDOW_WIDTH, WINDOW_HEIGTH);
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(vmode, "op", sf::Style::Resize, settings);
    window.setFramerateLimit(144);
    sf::Event event;

    Field field(sf::Vector2f(
            WINDOW_WIDTH / 2 - CELL_SIZE * M / 2,
            WINDOW_HEIGTH / 2 - CELL_SIZE * M));

    Brick* brick = nullptr;
    int random = rand() % 7;
    sf::Vector2i pos(3, 0);

    switch (random) {
    case 0:
        brick = new IBrick(pos);
        break;
    case 1:
        brick = new JBrick(pos);
        break;
    case 2:
        brick = new LBrick(pos);
        break;
    case 3:
        brick = new OBrick(pos);
        break;
    case 4:
        brick = new SBrick(pos);
        break;
    case 5:
        brick = new TBrick(pos);
        break;
    case 6:
        brick = new ZBrick(pos);
    default:
        break;
    }

    field.set_brick(*brick);

    sf::Clock time;

    sf::Vector2i movement;
    while (window.isOpen()) {
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
            default:
                break;
            }
        }

        if ((movement.y == 0 && time.getElapsedTime().asSeconds() >= 0.6)) {
            movement.y = 1;
            time.restart();
        }

        if (movement.y || movement.x) {
            sf::Vector2i prev_pos[4];
            (*brick).write_position(prev_pos);
            (*brick).move(movement);
            field.clear_and_set_brick(*brick, prev_pos);
        }

        movement = {0, 0};

        window.clear();
        window.draw(field);
        window.display();
    }

    return 0;
}