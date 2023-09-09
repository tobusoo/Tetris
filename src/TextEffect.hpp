#include <SFML/Graphics.hpp>

#include "Option.hpp"

class TextEffect : public sf::Drawable {
public:
    TextEffect(sf::Vector2f pos, unsigned int size, sf::String str) noexcept
        : font_size(size), font_position(pos)
    {
        if (!font.loadFromFile("resource/font.otf"))
            exit(EXIT_FAILURE);

        text.setFont(font);
        text.setPosition(font_position);
        text.setFillColor(sf::Color::White);
        text.setCharacterSize(font_size);
        text.setString(str);
    }

    void setString(const sf::String& str) noexcept
    {
        text.setString(str);
    }

    void show() noexcept
    {
        time.restart();
        showing = true;
    }

    void update(float dt) noexcept
    {
        if (showing && time.getElapsedTime().asSeconds() <= 0.5) {
            text.setCharacterSize(
                    text.getCharacterSize() - (font_size * 2 * dt));
            text.move(sf::Vector2f(font_size * 2 * dt, font_size * 5 * dt));
        } else {
            text.setPosition(font_position);
            text.setCharacterSize(font_size);
            showing = false;
        }
    }

    bool is_showing() const noexcept
    {
        return showing;
    }

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        if (showing)
            target.draw(text, states);
    }

private:
    sf::Font font;
    sf::Text text;
    size_t font_size;

    sf::Clock time;
    sf::Vector2f font_position;

    bool showing = false;
};