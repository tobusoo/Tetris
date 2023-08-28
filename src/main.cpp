#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <vector>

#include "Bricks.h"
#include "Field.hpp"
#include "Option.hpp"

int b1 = 0;
int b2 = 0;
int b3 = 0;
int b4 = 0;
int b5 = 0;
int b6 = 0;
int b7 = 0;

std::random_device random_device;
std::default_random_engine random_engine(random_device());
std::uniform_int_distribution<unsigned short> dist(0, 6);

Brick* newBrick()
{
    unsigned short random = dist(random_engine);

    sf::Vector2i pos(3, 0);
    Brick* brick = nullptr;

    switch (random) {
    case 0:
        brick = new IBrick(pos);
        b1++;
        break;
    case 1:
        brick = new JBrick(pos);
        b2++;
        break;
    case 2:
        brick = new LBrick(pos);
        b3++;
        break;
    case 3:
        brick = new OBrick(pos);
        b4++;
        break;
    case 4:
        b5++;
        brick = new SBrick(pos);
        break;
    case 5:
        b6++;
        brick = new TBrick(pos);
        break;
    case 6:
        b7++;
        brick = new ZBrick(pos);
    }

    return brick;
}

int main()
{
    sf::VideoMode vmode(WINDOW_WIDTH, WINDOW_HEIGTH);
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(vmode, "op", sf::Style::Resize, settings);
    window.setPosition(sf::Vector2i(200, 0));
    window.setFramerateLimit(144);
    sf::Event event;

    Field field(sf::Vector2f(
            WINDOW_WIDTH / 2 - CELL_SIZE * M / 2,
            WINDOW_HEIGTH / 2 - CELL_SIZE * M));

    Brick* brick = newBrick();

    field.set_brick(*brick, true);

    sf::Vector2i movement;
    bool rotate_key = false;
    bool fast_down = false;

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
                if (event.key.code == sf::Keyboard::Up)
                    fast_down = true;
            default:
                break;
            }
        }

        field.update((*brick), movement, rotate_key, fast_down);
        movement = {0, 0};
        rotate_key = false;
        fast_down = false;

        if (field.collide(*brick) && field.need_new_brick()) {
            field.set_brick(*brick);
            field.reset_time();
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
    std::cout << "statisic:\n";
    std::cout << b1 << '\n';
    std::cout << b2 << '\n';
    std::cout << b3 << '\n';
    std::cout << b4 << '\n';
    std::cout << b5 << '\n';
    std::cout << b6 << '\n';
    std::cout << b7 << '\n';

    return 0;
}