#include <TextEffect.hpp>

TextEffect::TextEffect(
        sf::Vector2f pos, unsigned int size, sf::String str) noexcept
    : font_size(size), text_position(pos)
{
    if (!font.loadFromFile("resource/font.otf"))
        exit(EXIT_FAILURE);

    text.setFont(font);
    text.setPosition(text_position);
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(font_size);
    text.setString(str);
}

void TextEffect::setString(const sf::String& str) noexcept
{
    text.setString(str);
}

void TextEffect::show() noexcept
{
    time.restart();
    showing = true;
}

void TextEffect::update(float dt) noexcept
{
    if (showing && time.getElapsedTime().asSeconds() <= 0.5) {
        text.setCharacterSize(text.getCharacterSize() - (font_size * 2 * dt));
        text.move(sf::Vector2f(font_size * 2 * dt, font_size * 5 * dt));
    } else {
        text.setPosition(text_position);
        text.setCharacterSize(font_size);
        showing = false;
    }
}

bool TextEffect::is_showing() const noexcept
{
    return showing;
}

void TextEffect::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if (showing)
        target.draw(text, states);
}
