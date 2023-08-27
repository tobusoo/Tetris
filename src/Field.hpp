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
    }

    Field(sf::Vector2f position)
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
    }

    void clear_and_move_brick(Brick& brick, const sf::Vector2i* prev_pos)
    {
        // clear prev_pos
        for (int i = 0; i < 4; i++) {
            fill_matrix[(prev_pos + i)->y][(prev_pos + i)->x] = 0;
            matrix[(prev_pos + i)->y][(prev_pos + i)->x].setFillColor(
                    sf::Color(224, 224, 224));
            matrix[(prev_pos + i)->y][(prev_pos + i)->x].setFillColor(
                    sf::Color::Transparent);
        }

        sf::Vector2i current_pos[4];
        brick.write_position(current_pos);

        for (int i = 0; i < 4; i++) {
            matrix[current_pos[i].y][current_pos[i].x].setFillColor(
                    brick.get_color());
        }
    }

    void set_brick(Brick& brick, bool first = false)
    {
        sf::Vector2i current_pos[4];
        brick.write_position(current_pos);

        for (int i = 0; i < 4; i++) {
            if (!first)
                fill_matrix[current_pos[i].y][current_pos[i].x] = 1;
            matrix[current_pos[i].y][current_pos[i].x].setFillColor(
                    brick.get_color());
        }
    }

    bool collide(Brick& brick)
    {
        sf::Vector2i current_pos[4];
        brick.write_position(current_pos);
        double elapsed_time = time.getElapsedTime().asSeconds();

        for (int i = 0; i < 4; i++) {
            if (current_pos[i].y > N - 2)
                return true;
            if (fill_matrix[current_pos[i].y + 1][current_pos[i].x] == 1
                && elapsed_time > 0.1)
                return true;
        }

        return false;
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
            if (line) {
                drop_down(i);
            }
        }
    }

    void move(Brick& brick, sf::Vector2i dxdy, bool rotate_key = false)
    {
        sf::Vector2i prev_pos[4];
        sf::Vector2i current_pos[4];
        brick.write_position(current_pos);

        double elapsed_time = time.getElapsedTime().asSeconds();

        if (rotate_key) {
            // TODO: need to check collision!!!!!!
            brick.write_position(prev_pos);
            brick.rotate();

            if (collide(brick) || brick.is_out_of_screen()) {
                brick.set_position(prev_pos);
                brick.reset_state();
            }

            clear_and_move_brick(brick, prev_pos);
            brick.write_position(current_pos);
            brick.write_position(prev_pos);
        }

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

        if (dxdy.y == 1) {
            for (int i = 0; i < 4; i++) {
                if (fill_matrix[current_pos[i].y + 1][current_pos[i].x] == 1) {
                    dxdy.y = 0;
                    break;
                }
            }
        }

        if (elapsed_time >= 0.6) {
            dxdy.y = 1;
            time.restart();
        }

        brick.write_position(prev_pos);
        brick.move(dxdy);
        clear_and_move_brick(brick, prev_pos);
    }

    bool end()
    {
        for (int i = 0; i < M; i++) {
            if (fill_matrix[0][i])
                return true;
        }
        return false;
    }

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates state) const
    {
        for (auto& i : matrix) {
            for (auto& j : i) {
                target.draw(j);
            }
        }
    }

    sf::RectangleShape matrix[N][M];
    bool fill_matrix[N][M] = {0};
    sf::Clock time;
};