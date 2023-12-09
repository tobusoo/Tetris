#include <SFML/Graphics.hpp>
#include <iostream>

#include <Bricks.h>
#include <BricksGenerator.hpp>
#include <Field.hpp>
#include <NextBrickPanel.hpp>
#include <Option.hpp>
#include <StatisticPanel.hpp>

class Game {
public:
    Game()
        : video_mode(WINDOW_WIDTH, WINDOW_HEIGTH),
          settings(0, 0, 8),
          window(video_mode, "Tetris & Tobuso", sf::Style::Resize, settings),
          field({WINDOW_WIDTH / 2 - CELL_SIZE * M / 2,
                 WINDOW_HEIGTH / 2 - CELL_SIZE * M}),
          stat_panel({20, WINDOW_HEIGTH / 2 - CELL_SIZE * M}),
          next_panel({{580, WINDOW_HEIGTH / 2 - CELL_SIZE * M}}),
          brick(nullptr),
          next_brick(nullptr),
          dt(0)
    {
        window.setPosition({200, 0});
        window.setFramerateLimit(FPS);

        if (!font.loadFromFile("resource/font.otf"))
            exit(EXIT_FAILURE);

        restart_text.setFont(font);
        restart_text.setString("Press R to\n restart!");
        restart_text.setCharacterSize(56);
        restart_text.setFillColor(sf::Color::White);
        restart_text.setPosition(
                {WINDOW_WIDTH / 2 - CELL_SIZE * M / 2, WINDOW_HEIGTH / 3});

        new_brick();
    }

    ~Game()
    {
        delete brick;
        delete next_brick;
    }

    void start() noexcept
    {
        while (window.isOpen()) {
            if (!end_game)
                game_loop();

            input_handler();
            render();
            if (end_game && reset_game) {
                end_game = false;
                reset_game = false;
                reset_input();
                field.reset_game();
                stat_panel.reset();
                new_brick();
            }
        }
    }

protected:
    void new_brick() noexcept
    {
        if (brick != nullptr) {
            delete brick;
            brick = nullptr;
        }
        if (next_brick != nullptr) {
            delete next_brick;
            next_brick = nullptr;
        }

        brick = generator.get_random_brick();
        brick->move({3, 0});
        field.set_brick(*brick, true);
        stat_panel.increase_i_brick(generator.get_last_i());

        next_brick = generator.get_random_brick();
        next_panel.set_brick(*next_brick);
    }

    void reset_input() noexcept
    {
        movement = {0, 0};
        right_rotate = false;
        left_rotate = false;
        fast_drop = false;
        reset_game = false;
    }

    void game_loop() noexcept
    {
        while (window.isOpen()) {
            dt = time.getElapsedTime().asSeconds();
            time.restart();

            input_handler();

            field.update(
                    *brick, movement, dt, right_rotate, left_rotate, fast_drop);
            reset_input();

            if (field.collide(*brick) && field.need_new_brick()) {
                stat_panel.increase_i_brick(generator.get_last_i());
                field.set_brick(*brick);
                field.reset_time();
                delete brick;

                brick = next_brick;
                brick->move(sf::Vector2i(3, 0));
                next_brick = generator.get_random_brick();

                next_panel.set_brick(*next_brick);
            }

            if (field.check_lines()) {
                stat_panel.set_lines(field.get_lines());
                stat_panel.set_score(field.get_score());
            }

            render();

            if (field.is_end()) {
                std::cout << "Your score: " << stat_panel.get_score() << '\n';
                std::cout << "Your Lines: " << stat_panel.get_lines() << '\n';
                std::cout << "Press R to restart!\n";
                end_game = true;
                return;
            }
        }
    }

    void render() noexcept
    {
        window.clear(sf::Color(60, 60, 60));
        window.draw(field);
        window.draw(next_panel);
        window.draw(stat_panel);
        if (end_game)
            window.draw(restart_text);
        window.display();
    }

    void input_handler() noexcept
    {
        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
                if (event.key.code == sf::Keyboard::Down)
                    movement.y = 1;
                if (event.key.code == sf::Keyboard::Left)
                    movement.x = -1;
                if (event.key.code == sf::Keyboard::Right)
                    movement.x = 1;
                if (event.key.code == sf::Keyboard::D)
                    right_rotate = true;
                if (event.key.code == sf::Keyboard::A)
                    left_rotate = true;
                if (event.key.code == sf::Keyboard::Space)
                    fast_drop = true;
                if (event.key.code == sf::Keyboard::R)
                    reset_game = true;
            default:
                break;
            }
        }
    }

private:
    sf::VideoMode video_mode;
    sf::ContextSettings settings;
    sf::RenderWindow window;
    sf::Event event;

    sf::Font font;
    sf::Text restart_text;

    Field field;
    StatisticPanel stat_panel;
    NextBrickPanel next_panel;
    BricksGenerator generator;

    Brick* brick;
    Brick* next_brick;

    sf::Clock time;
    sf::Vector2i movement;
    float dt;

    bool right_rotate = false;
    bool left_rotate = false;
    bool fast_drop = false;
    bool end_game = false;
    bool reset_game = false;
};