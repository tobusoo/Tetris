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
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                matrix[i][j].setFillColor(sf::Color(224, 224, 224));
                matrix[i][j].setSize(
                        sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1));
                matrix[i][j].setPosition(
                        sf::Vector2f(i * CELL_SIZE, j * CELL_SIZE));
            }
        }
    }

    Field(sf::Vector2f position)
    {
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                matrix[i][j].setFillColor(sf::Color(224, 224, 224));
                matrix[i][j].setSize(
                        sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1));
                matrix[i][j].setPosition(sf::Vector2f(
                        i * CELL_SIZE + position.x,
                        j * CELL_SIZE + position.y));
            }
        }
    }

    void clear_and_set_brick(Brick& brick, const sf::Vector2i* prev_pos)
    {
        // clear prev_pos
        for (int i = 0; i < 4; i++) {
            fill_matrix[(prev_pos + i)->x][(prev_pos + i)->y] = 0;
            matrix[(prev_pos + i)->x][(prev_pos + i)->y].setFillColor(
                    sf::Color(224, 224, 224));
        }

        set_brick(brick);
    }

    void set_brick(Brick& brick)
    {
        const sf::Vector2i* pos = brick.get_position();
        for (int i = 0; i < 4; i++) {
            fill_matrix[(pos + i)->x][(pos + i)->y] = 1;
            matrix[(pos + i)->x][(pos + i)->y].setFillColor(brick.get_color());
        }
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

    sf::RectangleShape matrix[M][N];
    unsigned char fill_matrix[M][N] = {0};
};