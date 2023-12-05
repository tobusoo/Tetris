#pragma once

#include <SFML/Graphics.hpp>

#include <Bricks.h>
#include <DropEffect.hpp>
#include <TextEffect.hpp>

class Field : public sf::Drawable {
public:
    Field() noexcept;
    Field(const sf::Vector2f position) noexcept;

    void set_brick(const Brick& brick, bool first = false) noexcept;
    void set_ghost_brick(const Brick& brick) noexcept;

    size_t get_lines() const noexcept;
    size_t get_score() const noexcept;

    void reset_time() noexcept;
    void check_lines() noexcept;
    void
    update(Brick& brick,
           sf::Vector2i dxdy,
           float dt,
           bool right_rotate,
           bool left_rotate,
           bool fast_down) noexcept;

    bool
    collide(const Brick& brick, sf::Vector2i fix_collide[4] = nullptr) noexcept;
    bool need_new_brick() noexcept;
    bool end() const noexcept;

private:
    void draw(sf::RenderTarget& target, sf::RenderStates state) const;

    void rotate_brick(
            Brick& brick, sf::Vector2i prev_pos[4], bool is_right) noexcept;
    void remove_filled_line(int i) noexcept;
    void instant_drop(Brick& brick, sf::Vector2i prev_pos[4]) noexcept;
    void movement_collision(
            sf::Vector2i& dxdy, const sf::Vector2i current_pos[4]) noexcept;
    void
    clear_and_move_brick(Brick& brick, const sf::Vector2i prev_pos[4]) noexcept;

private:
    sf::RectangleShape matrix[N][M];
    bool fill_matrix[N][M] = {0};

    bool bottom_collision = false;
    sf::Clock auto_drop;
    sf::Clock time_to_move;

    bool fast_drop = false;

    DropEffect drop_effect[4];
    TextEffect text_effect;
    sf::Clock effect_timer;
    const float effect_max_time = 0.2;

    size_t lines = 0;
    size_t score = 0;
    sf::Vector2f field_position;

    GhostBrick ghost_brick;
    sf::RectangleShape background;
};