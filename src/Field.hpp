#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "Brick.hpp"
#include "Option.hpp"

class Field : public sf::Drawable {
public:
    Field()
    {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                // matrix[i][j].setFillColor(sf::Color(224, 224, 224));
                matrix[i][j].setFillColor(sf::Color::Transparent);
                matrix[i][j].setOutlineColor(sf::Color(224, 224, 224));
                matrix[i][j].setOutlineThickness(1);

                matrix[i][j].setSize(
                        sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1));
                matrix[i][j].setPosition(
                        sf::Vector2f(j * CELL_SIZE, i * CELL_SIZE));
            }
        }

        ghost_brick = new IBrick(sf::Vector2i(3, 0));
        ghost_brick->set_color(sf::Color::White);
    }

    Field(const sf::Vector2f position)
    {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                // matrix[i][j].setFillColor(sf::Color(224, 224, 224));
                matrix[i][j].setFillColor(sf::Color::Transparent);
                matrix[i][j].setOutlineColor(sf::Color(224, 224, 224));
                matrix[i][j].setOutlineThickness(1);

                matrix[i][j].setSize(
                        sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1));
                matrix[i][j].setPosition(sf::Vector2f(
                        j * CELL_SIZE + position.x,
                        i * CELL_SIZE + position.y));
            }
        }

        ghost_brick = new IBrick(sf::Vector2i(3, 0));
        ghost_brick->set_color(sf::Color::White);
    }

    void set_brick(const Brick& brick, bool first = false) noexcept
    {
        sf::Vector2i current_pos[4];
        brick.write_position(current_pos);

        for (int i = 0; i < 4; i++) {
            if (!first)
                fill_matrix[current_pos[i].y][current_pos[i].x] = 1;
            matrix[current_pos[i].y][current_pos[i].x].setFillColor(
                    brick.get_color());
            matrix[current_pos[i].y][current_pos[i].x].setOutlineThickness(1);
            matrix[current_pos[i].y][current_pos[i].x].setOutlineColor(
                    sf::Color::White);
        }
        for (int i = 0; i < 4; i++) {
            ghost_prev_pos[i] = {0, 0};
        }
    }

    bool
    collide(const Brick& brick, sf::Vector2i fix_collide[4] = nullptr) noexcept
    {
        sf::Vector2i current_pos[4];
        brick.write_position(current_pos);
        int collide_with_bricks = 0;

        for (int i = 0; i < 4; i++) {
            if (current_pos[i].y > N - 2) {
                if (!botton_collision) {
                    time_to_move.restart();
                    botton_collision = true;
                }
                return true;
            }
            if (fill_matrix[current_pos[i].y + 1][current_pos[i].x] == 1) {
                collide_with_bricks = i + 1;
                break;
            }
            if (fill_matrix[current_pos[i].y][current_pos[i].x] == 1
                && fix_collide) {
                fix_collide[0].x = 69;
                return true;
            }
        }

        if (collide_with_bricks) {
            if (fix_collide != nullptr) {
                sf::Vector2i left = brick.get_leftmost_position();
                sf::Vector2i right = brick.get_rightmost_position();
                sf::Vector2i center = brick.get_center_position();
                sf::Vector2i diff;

                if (center.x < current_pos[collide_with_bricks - 1].x) {
                    diff.x -= right.x - center.x; // need to left
                    if (diff.x == 0)
                        diff.x = -1;
                } else {
                    diff.x += center.x - left.x; // need to right
                    if (diff.x == 0)
                        diff.x = 1;
                }

                for (int i = 0; i < 4; i++) {
                    fix_collide[i] = current_pos[i] + diff;
                }
            } else {
                if (!botton_collision) {
                    time_to_move.restart();
                    botton_collision = true;
                }
            }

            return true;
        }

        botton_collision = false;
        return false;
    }

    void check_lines() noexcept
    {
        for (int i = 0; i < N; i++) {
            bool line = true;
            for (int j = 0; j < M; j++) {
                if (fill_matrix[i][j] == 0) {
                    line = false;
                    break;
                }
            }
            if (line)
                drop_down(i);
        }
    }

    void reset_time() noexcept
    {
        time_to_move.restart();
        botton_collision = false;
    }

    void
    update(Brick& brick,
           sf::Vector2i dxdy,
           bool rotate_key,
           bool fast_down) noexcept
    {
        sf::Vector2i positions[4];
        if (rotate_key) {
            rotate_brick(brick, positions);
        }

        if (fast_down) {
            fast_brick_down(brick, positions);
            return;
        }

        brick.write_position(positions);
        movement_collision(dxdy, positions);

        brick.write_position(positions);
        brick.move(dxdy);

        clear_and_move_brick(brick, positions);
        set_ghost_brick(brick);
    }

    void set_ghost_brick(const Brick& brick)
    {
        sf::Vector2i prev_pos[4];
        brick.write_position(prev_pos);
        ghost_brick->set_position(prev_pos);

        while (!collide(*ghost_brick)) {
            ghost_brick->move({0, 1});
        }

        clear_and_move_brick(*ghost_brick, ghost_prev_pos);
        ghost_brick->write_position(ghost_prev_pos);
    }

    bool need_new_brick() noexcept
    {
        if (fast_down) {
            fast_down = false;
            return true;
        }
        return time_to_move.getElapsedTime().asSeconds() >= 0.5
                && botton_collision;
    }

    bool end() const noexcept
    {
        for (int i = 0; i < M; i++) {
            if (fill_matrix[0][i])
                return true;
        }
        return false;
    }

private:
    void draw(sf::RenderTarget& target, sf::RenderStates state) const
    {
        for (auto& i : matrix) {
            for (auto& j : i) {
                target.draw(j);
            }
        }
    }

    void drop_down(int i) noexcept
    {
        for (int ii = i; ii > 0; ii--) {
            for (int j = 0; j < M; j++) {
                fill_matrix[ii][j] = fill_matrix[ii - 1][j];
                matrix[ii][j].setFillColor(matrix[ii - 1][j].getFillColor());
            }
        }
    }

    void rotate_brick(Brick& brick, sf::Vector2i prev_pos[4]) noexcept
    {
        brick.write_position(prev_pos);
        brick.rotate();

        sf::Vector2i leftmost_pos;
        sf::Vector2i rightmost_pos;

        // Check collision with screen
        if (brick.is_out_of_screen(leftmost_pos, rightmost_pos)) {
            if (leftmost_pos.x < 0)
                brick.move(sf::Vector2i(-leftmost_pos.x, 0));
            else
                brick.move(sf::Vector2i(-(rightmost_pos.x - M) - 1, 0));
        }

        // Check collision with field
        sf::Vector2i fix_collide[4];
        if (collide(brick, fix_collide)) {
            if (fix_collide[0].x == 69) {
                brick.reset_state();
                brick.set_position(prev_pos);
            } else {
                brick.set_position(fix_collide);
                if (collide(brick) || brick.is_out_of_screen()) {
                    brick.reset_state();
                    brick.set_position(prev_pos);
                }
            }
        }
        auto top = brick.get_highter_position();

        if (top.y < 0) {
            brick.reset_state();
            brick.set_position(prev_pos);
        }

        clear_and_move_brick(brick, prev_pos);
        brick.write_position(prev_pos);
    }

    void fast_brick_down(Brick& brick, sf::Vector2i prev_pos[4]) noexcept
    {
        while (!collide(brick)) {
            brick.write_position(prev_pos);
            brick.move({0, 1});
            clear_and_move_brick(brick, prev_pos);
        }

        botton_collision = true;
        fast_down = true;
        set_brick(brick);
    }

    void movement_collision(
            sf::Vector2i& dxdy, const sf::Vector2i current_pos[4]) noexcept
    {
        double elapsed_time = time_to_lower_brick.getElapsedTime().asSeconds();

        if (dxdy.x == 1) {
            for (int i = 0; i < 4; i++) {
                if (fill_matrix[current_pos[i].y][current_pos[i].x + 1] == 1) {
                    dxdy.x = 0;
                    break;
                }
            }
        } else if (dxdy.x == -1) {
            for (int i = 0; i < 4; i++) {
                if (fill_matrix[current_pos[i].y][current_pos[i].x - 1] == 1) {
                    dxdy.x = 0;
                    break;
                }
            }
        }

        // if (dxdy.y == 1) {
        //     for (int i = 0; i < 4; i++) {
        //         if (fill_matrix[current_pos[i].y + 1][current_pos[i].x] == 1)
        //         {
        //             dxdy.y = 0;
        //             break;
        //         }
        //     }
        // }

        if (elapsed_time >= 0.6) {
            dxdy.y = 1;
            time_to_lower_brick.restart();
        }

        if (botton_collision)
            dxdy.y = 0;
    }

    void
    clear_and_move_brick(Brick& brick, const sf::Vector2i prev_pos[4]) noexcept
    {
        // clear prev_pos
        for (int i = 0; i < 4; i++) {
            fill_matrix[prev_pos[i].y][prev_pos[i].x] = 0;
            // matrix[prev_pos[i].y][prev_pos[i].x].setFillColor(
            //         sf::Color(224, 224, 224));
            matrix[prev_pos[i].y][prev_pos[i].x].setFillColor(
                    sf::Color::Transparent);
            matrix[prev_pos[i].y][prev_pos[i].x].setOutlineThickness(1);
            matrix[prev_pos[i].y][prev_pos[i].x].setOutlineColor(
                    sf::Color::White);
        }

        sf::Vector2i current_pos[4];
        brick.write_position(current_pos);

        sf::Color color = brick.get_color();
        for (int i = 0; i < 4; i++) {
            if (color == sf::Color::White) {
                matrix[current_pos[i].y][current_pos[i].x].setFillColor(
                        sf::Color::Transparent);
                matrix[current_pos[i].y][current_pos[i].x].setOutlineColor(
                        color);
                matrix[current_pos[i].y][current_pos[i].x].setOutlineThickness(
                        2);
            } else
                matrix[current_pos[i].y][current_pos[i].x].setFillColor(color);
        }
    }

private:
    sf::RectangleShape matrix[N][M];
    bool fill_matrix[N][M] = {0};
    sf::Clock time_to_lower_brick;

    Brick* ghost_brick;
    sf::Vector2i ghost_prev_pos[4];

    bool botton_collision = false;
    sf::Clock time_to_move;
    bool fast_down = false;
};