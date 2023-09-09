#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <vector>

class DropEffect : public sf::Drawable {
public:
    DropEffect(
            sf::Color color,
            sf::Vector2f pos,
            sf::Vector2f size_,
            float max_time_)
        : max_time(max_time_)
    {
        if (!texture.loadFromFile("image.png")) {
            std::cout << "Fail to load image\n";
            exit(EXIT_FAILURE);
        }

        if (!shader.loadFromFile(
                    "fragment_shader.glsl", sf::Shader::Fragment)) {
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
        body.setPosition(position);
        body.setSize(size);
        shader.setUniform("time", static_cast<float>(0));
        time.restart();
    }

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(body, &shader);
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

int main()
{
    sf::VideoMode vmode(800, 600);
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(vmode, "op", sf::Style::Resize, settings);
    window.setFramerateLimit(144);
    sf::Event event;

    sf::Texture texture;
    if (!texture.loadFromFile("image.png")) {
        std::cout << "Fail to load image\n";
        return -1;
    }

    sf::RectangleShape rec;
    rec.setTexture(&texture);
    rec.setFillColor(sf::Color(sf::Color(128, 128, 128)));
    // rec.setFillColor(sf::Color(204, 102, 0));
    rec.setSize(sf::Vector2f(50, 200));
    rec.setPosition(100, 100);

    sf::RectangleShape rec2 = rec;
    rec2.setPosition(200, 100);

    sf::Shader shader;
    if (!shader.loadFromFile("fragment_shader.glsl", sf::Shader::Fragment)) {
        std::cout << "Fail to load shader\n";
        return -1;
    }

    if (!shader.isAvailable()) {
        std::cout << "The shader is not available\n";
    }

    bool go = false;
    sf::Clock time;

    double max_time = 0.2;

    shader.setUniform("max_time", static_cast<float>(max_time));

    const float diff = 200 / max_time / 144;
    DropEffect ef(sf::Color::Green, {300, 100}, {25, 200}, max_time);

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
                if (event.key.code == sf::Keyboard::Enter) {
                    go = true;
                    time.restart();
                }
                break;
            default:
                break;
            }
        }

        if (time.getElapsedTime().asSeconds() >= max_time + 0.01
            || rec.getSize().y <= 0) {
            rec.setSize(sf::Vector2f(50, 200));
            rec2.setSize(sf::Vector2f(50, 200));
            rec.setPosition(100, 100);
            rec2.setPosition(200, 100);
            time.restart();
            shader.setUniform("time", (float)0);
            ef.reset();
            go = false;
        } else if (go) {
            sf::Vector2f size = rec.getSize();
            sf::Vector2f pos1 = rec.getPosition();
            auto pos2 = rec2.getPosition();

            pos1.y += diff;
            pos2.y += diff;

            size.y -= diff;
            rec.setSize(size);
            rec2.setSize(size);

            rec.setPosition(pos1);
            rec2.setPosition(pos2);

            ef.update();
            double elapsed_time = time.getElapsedTime().asSeconds();
            shader.setUniform("time", static_cast<float>(elapsed_time));
        } else {
            shader.setUniform("time", static_cast<float>(0));
            ef.reset();
        }

        window.clear();
        window.draw(rec, &shader);
        window.draw(ef);
        window.draw(rec2);
        window.display();
    }

    return 0;
}