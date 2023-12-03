#pragma once

#include <SFML/Graphics.hpp>

class DropEffect : public sf::Drawable {
public:
    DropEffect();
    DropEffect(
            sf::Color color,
            sf::Vector2f pos,
            sf::Vector2f size_,
            float max_time_);

    void set_size(sf::Vector2f size_);
    void set_max_time(float max_time_);
    void set_color(sf::Color clr);
    void set_position(sf::Vector2f position_);

    void update();
    void reset();

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    sf::RectangleShape body;
    sf::Texture texture;
    sf::Shader shader;

    sf::Clock time;
    sf::Vector2f position;
    sf::Vector2f size;

    float max_time;
    float diff;
};