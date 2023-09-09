#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class DropEffect : public sf::Drawable {
public:
    DropEffect(
            sf::Color color,
            sf::Vector2f pos,
            sf::Vector2f size_,
            float max_time_)
        : max_time(max_time_)
    {
        if (!texture.loadFromFile("resource/image.png")) {
            std::cout << "Fail to load image\n";
            exit(EXIT_FAILURE);
        }

        if (!shader.loadFromFile(
                    "resource/fragment_shader.glsl", sf::Shader::Fragment)) {
            std::cout << "Fail to load shader\n";
            exit(EXIT_FAILURE);
        }

        if (!shader.isAvailable()) {
            std::cout << "The shader is not available\n";
        }

        body.setTexture(&texture);
        body.setFillColor(color);
        body.setSize(size_);
        body.setPosition(pos);
        size = size_;

        position = pos;
        diff = size.y / max_time / 144; // 144 - FPS
        shader.setUniform("max_time", max_time);
        time.restart();
    }

    DropEffect() : DropEffect(sf::Color::White, {0, 0}, {0, 0}, 0)
    {
    }

    void set_size(sf::Vector2f size_)
    {
        size = size_;
        diff = size.y / max_time / 144;
        body.setSize(size);
    }

    void set_max_time(float max_time_)
    {
        max_time = max_time_;
        diff = size.y / max_time / 144;
        shader.setUniform("max_time", max_time);
    }

    void set_color(sf::Color clr)
    {
        body.setFillColor(clr);
    }

    void set_position(sf::Vector2f position_)
    {
        position = position_;
        body.setPosition(position);
    }

    void update()
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

    void reset()
    {
        time.restart();
        body.setPosition(position);
        body.setSize(size);
        shader.setUniform("time", static_cast<float>(0));
    }

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(body, &shader);
        // target.draw(body);
    }

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