#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "Bricks.h"
#include "Field.hpp"
#include "Option.hpp"

Brick* newBrick()
{
    int random = rand() % 7;
    sf::Vector2i pos(3, 0);
    Brick* brick = nullptr;

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
    }

    return brick;
}

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

    Brick* brick = newBrick();

    field.set_brick(*brick, true);

    sf::Vector2i movement;
    bool rotate_key = false;

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
                if (event.key.code == sf::Keyboard::Space)
                    rotate_key = true;
            default:
                break;
            }
        }

        field.move((*brick), movement, rotate_key);
        movement = {0, 0};
        rotate_key = false;

        if (field.collide(*brick)) {
            field.set_brick(*brick);
            delete brick;
            brick = newBrick();
        }

        field.check_lines();

        window.clear();
        window.draw(field);
        window.display();

        if (field.end()) {
            std::cout << "game end\n";
            window.close();
        }
    }

    return 0;
}