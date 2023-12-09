#include <DropEffect.hpp>
#include <Option.hpp>

DropEffect::DropEffect(
        sf::Color color, sf::Vector2f pos, sf::Vector2f size_, float max_time_)
    : max_time(max_time_)
{
    if (!texture.loadFromFile("resource/image.png")) {
        exit(EXIT_FAILURE);
    }

    if (!shader.loadFromFile(
                "resource/fragment_shader.glsl", sf::Shader::Fragment)) {
        exit(EXIT_FAILURE);
    }

    body.setTexture(&texture);
    body.setFillColor(color);
    body.setSize(size_);
    body.setPosition(pos);
    size = size_;

    position = pos;
    diff = size.y / max_time / FPS;
    shader.setUniform("max_time", max_time);
    time.restart();
}

DropEffect::DropEffect() : DropEffect(sf::Color::White, {0, 0}, {0, 0}, 0)
{
}

void DropEffect::set_size(sf::Vector2f size_) noexcept
{
    size = size_;
    diff = size.y / max_time / FPS;
    body.setSize(size);
}

void DropEffect::set_max_time(float max_time_) noexcept
{
    max_time = max_time_;
    diff = size.y / max_time / FPS;
    shader.setUniform("max_time", max_time);
}

void DropEffect::set_color(sf::Color clr) noexcept
{
    body.setFillColor(clr);
}

void DropEffect::set_position(sf::Vector2f position_) noexcept
{
    position = position_;
    body.setPosition(position);
}

void DropEffect::update() noexcept
{
    auto size = body.getSize();
    auto pos = body.getPosition();

    pos.y += diff;
    size.y -= diff;

    body.setSize(size);
    body.setPosition(pos);

    double elapsed_time = time.getElapsedTime().asSeconds();
    shader.setUniform("time", static_cast<float>(elapsed_time));
}

void DropEffect::reset() noexcept
{
    time.restart();
    body.setPosition(position);
    body.setSize(size);
    shader.setUniform("time", static_cast<float>(0));
}

void DropEffect::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
    state = sf::RenderStates();
    target.draw(body, &shader);
}
