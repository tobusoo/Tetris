#pragma once

#include <Bricks.h>
#include <random>

class BricksGenerator {
public:
    BricksGenerator();

    unsigned short get_last_i() const noexcept;
    Brick* get_random_brick() noexcept;
    Brick* get_i_brick(unsigned short i) noexcept;

private:
    std::random_device random_device;
    std::default_random_engine random_engine;
    std::uniform_int_distribution<unsigned short> dist;

    unsigned short last_i;
};