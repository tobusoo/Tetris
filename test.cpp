#include <SFML/Graphics.hpp>
#include <iostream>

#include "src/Option.hpp"

class TextEffect : public sf::Drawable {
public:
    TextEffect(sf::Vector2f pos, unsigned int size, sf::String& str) noexcept
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

int main()
{
    sf::VideoMode vmode(WINDOW_WIDTH, WINDOW_HEIGTH);
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(vmode, "test", sf::Style::Resize, settings);
    window.setPosition(sf::Vector2i(600, 0));
    window.setFramerateLimit(60);

    const unsigned int font_size = 102;
    sf::Vector2f font_position(
            WINDOW_WIDTH / 2 - font_size, WINDOW_HEIGTH / 2 - font_size);

    sf::Event event;
    bool go = false;

    sf::String str("+1500");
    TextEffect effect(font_position, font_size, str);

    sf::Clock timer;
    while (window.isOpen()) {
        float dt = timer.getElapsedTime().asSeconds();
        timer.restart();

        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                switch (event.key.code) {
                case sf::Keyboard::Escape:
                    window.close();
                    break;
                case sf::Keyboard::Enter:
                    if (!go) {
                        effect.show();
                        go = true;
                    }
                default:
                    break;
                }
            default:
                break;
            }
        }

        effect.update(dt);

        go = effect.is_showing() == 0 ? false : true;

        window.clear();
        window.draw(effect);

        window.display();
    }

    window.close();

    return 0;
}