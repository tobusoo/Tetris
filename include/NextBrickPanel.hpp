#pragma once

#include <SFML/Graphics.hpp>

#include <bricks/Brick.hpp>

class NextBrickPanel : public sf::Drawable {
public:
    NextBrickPanel(sf::Vector2f position) noexcept;
    void set_brick(Brick& brick) noexcept;

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates state) const;

private:
    DrawableBrick next_brick;

    sf::Font font;
    sf::Text text;

    sf::RectangleShape background;
};