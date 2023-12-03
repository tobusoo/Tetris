#pragma once
#include <SFML/Graphics.hpp>

class TextEffect : public sf::Drawable {
public:
    TextEffect(sf::Vector2f pos, unsigned int size, sf::String str) noexcept;

    void update(float dt) noexcept;
    void setString(const sf::String& str) noexcept;
    void show() noexcept;
    bool is_showing() const noexcept;

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    sf::Font font;
    sf::Text text;
    size_t font_size;

    sf::Clock time;
    sf::Vector2f text_position;

    bool showing = false;
};