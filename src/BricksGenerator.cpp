#include <iostream>
#include <random>

#include <Bricks.h>
#include <BricksGenerator.hpp>

BricksGenerator::BricksGenerator()
    : random_engine(random_device()), dist(0, BRICKS_N - 1)
{
}

unsigned short BricksGenerator::get_last_i() const noexcept
{
    return last_i;
}

Brick* BricksGenerator::get_random_brick() noexcept
{
    return get_i_brick(dist(random_engine));
}

Brick* BricksGenerator::get_i_brick(unsigned short i) noexcept
{
    if (i > BRICKS_N - 1) {
        return nullptr;
    }

    sf::Vector2i pos(0, 0);
    Brick* brick = nullptr;

    try {
        switch (i) {
        case 0:
            brick = new IBrick(pos);
            last_i = i;
            break;
        case 1:
            brick = new JBrick(pos);
            last_i = i;
            break;
        case 2:
            brick = new LBrick(pos);
            last_i = i;
            break;
        case 3:
            brick = new OBrick(pos);
            last_i = i;
            break;
        case 4:
            brick = new SBrick(pos);
            last_i = i;
            break;
        case 5:
            brick = new TBrick(pos);
            last_i = i;
            break;
        case 6:
            brick = new ZBrick(pos);
            last_i = i;
        }
    } catch (std::bad_alloc& e) {
        std::cout << "BricksGenerator::get_i_brick: " << e.what() << '\n';
        exit(EXIT_FAILURE);
    }

    return brick;
}
