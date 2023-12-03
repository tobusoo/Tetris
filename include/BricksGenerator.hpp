#pragma once

#include <Bricks.h>
#include <random>

class BricksGenerator {
public:
    BricksGenerator() : random_engine(random_device()), dist(0, BRICKS_N - 1)
    {
    }

    unsigned short get_last_i() const noexcept;
    Brick* get_random_brick() noexcept;
    Brick* get_i_brick(unsigned short i);

private:
    std::random_device random_device;
    std::default_random_engine random_engine;
    std::uniform_int_distribution<unsigned short> dist;

    unsigned short last_i;
};