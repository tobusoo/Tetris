#include <Field.hpp>

Field::Field() noexcept
    : text_effect(
            {WINDOW_WIDTH / 2 - 102, WINDOW_HEIGTH / 2 - 102}, 102, "+100"),
      field_position({0, 0}),
      ghost_brick({0, 0})
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            matrix[i][j].setFillColor(sf::Color::Transparent);
            matrix[i][j].setOutlineColor(sf::Color(224, 224, 224, 255 / 4));
            matrix[i][j].setOutlineThickness(1);

            matrix[i][j].setSize(sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1));
            matrix[i][j].setPosition(
                    sf::Vector2f(j * CELL_SIZE, i * CELL_SIZE));
        }
    }

    background.setSize(sf::Vector2f(CELL_SIZE * M + 1, CELL_SIZE * N + 1));
    background.setFillColor(sf::Color::Transparent);
    background.setOutlineColor(sf::Color(224, 224, 224, 255 / 2));
    background.setOutlineThickness(3);
}

Field::Field(const sf::Vector2f position) noexcept
    : text_effect(
            {CELL_SIZE * M / 2 - 102 + position.x,
             CELL_SIZE * N / 2 - 102 + position.y},
            100,
            "+100"),
      field_position(position),
      ghost_brick(position)
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            // matrix[i][j].setFillColor(sf::Color(224, 224, 224));
            matrix[i][j].setFillColor(sf::Color::Transparent);
            matrix[i][j].setOutlineColor(sf::Color(224, 224, 224, 255 / 4));
            matrix[i][j].setOutlineThickness(1);

            matrix[i][j].setSize(sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1));
            matrix[i][j].setPosition(sf::Vector2f(
                    j * CELL_SIZE + position.x, i * CELL_SIZE + position.y));
        }
    }

    background.setPosition(position);
    background.setSize(sf::Vector2f(CELL_SIZE * M, CELL_SIZE * N));
    background.setFillColor(sf::Color::Transparent);
    background.setOutlineColor(sf::Color(224, 224, 224, 255 / 2));
    background.setOutlineThickness(3);
}

void Field::set_brick(const Brick& brick, bool first) noexcept
{
    sf::Vector2i current_pos[4];
    brick.write_position(current_pos);

    for (int i = 0; i < 4; i++) {
        if (!first)
            fill_matrix[current_pos[i].y][current_pos[i].x] = 1;
        matrix[current_pos[i].y][current_pos[i].x].setFillColor(
                brick.get_color());
        matrix[current_pos[i].y][current_pos[i].x].setOutlineThickness(1);
        matrix[current_pos[i].y][current_pos[i].x].setOutlineColor(
                sf::Color(224, 224, 224, 255 / 4));
    }
}

bool Field::collide(const Brick& brick, sf::Vector2i fix_collide[4]) noexcept
{
    sf::Vector2i current_pos[4];
    brick.write_position(current_pos);
    int collide_with_bricks = 0;

    for (int i = 0; i < 4; i++) {
        if (current_pos[i].y > N - 2) {
            if (!bottom_collision) {
                time_to_move.restart();
                bottom_collision = true;
            }
            return true;
        }
        if (fill_matrix[current_pos[i].y + 1][current_pos[i].x] == 1) {
            collide_with_bricks = i + 1;
            break;
        }
        if (fill_matrix[current_pos[i].y][current_pos[i].x] == 1
            && fix_collide) {
            fix_collide[0].x = 69;
            return true;
        }
    }

    if (collide_with_bricks) {
        if (fix_collide != nullptr) {
            sf::Vector2i left = brick.get_leftmost_position();
            sf::Vector2i right = brick.get_rightmost_position();
            sf::Vector2i center = brick.get_center_position();
            sf::Vector2i diff;

            if (center.x < current_pos[collide_with_bricks - 1].x) {
                diff.x -= right.x - center.x; // need to left
                if (diff.x == 0)
                    diff.x = -1;
            } else {
                diff.x += center.x - left.x; // need to right
                if (diff.x == 0)
                    diff.x = 1;
            }

            for (int i = 0; i < 4; i++) {
                fix_collide[i] = current_pos[i] + diff;
            }
        } else {
            if (!bottom_collision) {
                time_to_move.restart();
                bottom_collision = true;
            }
        }

        return true;
    }

    bottom_collision = false;
    return false;
}

size_t Field::get_lines() const noexcept
{
    return lines;
}

size_t Field::get_score() const noexcept
{
    return score;
}

void Field::check_lines() noexcept
{
    size_t current_lines = 0;
    for (int i = 0; i < N; i++) {
        bool line = true;
        for (int j = 0; j < M; j++) {
            if (fill_matrix[i][j] == 0) {
                line = false;
                break;
            }
        }
        if (line) {
            current_lines++;
            remove_filled_line(i);
        }
    }

    size_t current_score = 0;
    if (current_lines == 1) {
        current_score = 100;
    } else if (current_lines == 2) {
        current_score = 300;
    } else if (current_lines == 3) {
        current_score = 700;
    } else if (current_lines == 4) {
        current_score = 1500;
    }

    if (current_lines > 0) {
        std::string str = "+" + std::to_string(current_score);
        text_effect.setString(str);
        text_effect.show();
    }

    score += current_score;
    lines += current_lines;
}

void Field::reset_time() noexcept
{
    time_to_move.restart();
    bottom_collision = false;
}

void Field::update(
        Brick& brick,
        sf::Vector2i dxdy,
        float dt,
        bool right_rotate,
        bool fast_down) noexcept
{
    sf::Vector2i positions[4];
    if (right_rotate) {
        rotate_brick(brick, positions);
    }

    if (effect_timer.getElapsedTime().asSeconds() <= effect_max_time) {
        for (int i = 0; i < 4; i++) {
            drop_effect[i].update();
        }
        return;
    }

    if (fast_down) {
        instant_drop(brick, positions);
        for (int i = 0; i < 4; i++) {
            drop_effect[i].update();
        }
        return;
    }

    brick.write_position(positions);
    movement_collision(dxdy, positions);

    brick.write_position(positions);
    brick.move(dxdy);

    clear_and_move_brick(brick, positions);
    set_ghost_brick(brick);
    text_effect.update(dt);
}

void Field::set_ghost_brick(const Brick& brick) noexcept
{
    sf::Vector2i prev_pos[4];
    brick.write_position(prev_pos);
    ghost_brick.set_position(prev_pos);
    ghost_brick.setOutlineColor(brick.get_color());

    while (!collide(ghost_brick)) {
        ghost_brick.move({0, 1});
    }

    ghost_brick.set_bricks_position();
}

bool Field::need_new_brick() noexcept
{
    if (fast_drop
        && effect_timer.getElapsedTime().asSeconds() >= effect_max_time) {
        fast_drop = false;
        return true;
    }

    return time_to_move.getElapsedTime().asSeconds() >= 0.5 && bottom_collision;
}

bool Field::end() const noexcept
{
    for (int i = 0; i < M; i++) {
        if (fill_matrix[0][i])
            return true;
    }

    return false;
}

void Field::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
    if (fast_drop) {
        for (auto& i : drop_effect) {
            target.draw(i);
        }
    }
    target.draw(background);
    target.draw(ghost_brick);
    for (auto& i : matrix) {
        for (auto& j : i) {
            target.draw(j);
        }
    }

    target.draw(text_effect, state);
}

void Field::remove_filled_line(int i) noexcept
{
    for (int ii = i; ii > 0; ii--) {
        for (int j = 0; j < M; j++) {
            fill_matrix[ii][j] = fill_matrix[ii - 1][j];
            matrix[ii][j].setFillColor(matrix[ii - 1][j].getFillColor());
        }
    }
}

void Field::rotate_brick(Brick& brick, sf::Vector2i prev_pos[4]) noexcept
{
    brick.write_position(prev_pos);
    brick.rotate();

    sf::Vector2i leftmost_pos;
    sf::Vector2i rightmost_pos;

    // Check collision with screen
    if (brick.is_out_of_screen(leftmost_pos, rightmost_pos)) {
        if (leftmost_pos.x < 0)
            brick.move(sf::Vector2i(-leftmost_pos.x, 0));
        else
            brick.move(sf::Vector2i(-(rightmost_pos.x - M) - 1, 0));
    }

    // Check collision with field
    sf::Vector2i fix_collide[4];
    if (collide(brick, fix_collide)) {
        if (fix_collide[0].x == 69) {
            brick.reset_state();
            brick.set_position(prev_pos);
        } else {
            brick.set_position(fix_collide);
            if (collide(brick) || brick.is_out_of_screen()) {
                brick.reset_state();
                brick.set_position(prev_pos);
            }
        }
    }
    auto top = brick.get_highter_position();

    if (top.y < 0) {
        brick.reset_state();
        brick.set_position(prev_pos);
    }

    clear_and_move_brick(brick, prev_pos);
    brick.write_position(prev_pos);
}

void Field::instant_drop(Brick& brick, sf::Vector2i prev_pos[4]) noexcept
{
    sf::Vector2i pos[4];
    sf::Vector2i after_pos[4];
    brick.write_position(pos);

    while (!collide(brick)) {
        brick.write_position(prev_pos);
        brick.move({0, 1});
        clear_and_move_brick(brick, prev_pos);
    }
    brick.write_position(after_pos);

    for (int i = 0; i < 4; i++) {
        drop_effect[i].set_position(sf::Vector2f(
                pos[i].x * CELL_SIZE + field_position.x,
                pos[i].y * CELL_SIZE + field_position.y));
        drop_effect[i].set_size(sf::Vector2f(
                CELL_SIZE, (after_pos[i].y - pos[i].y) * CELL_SIZE));
        drop_effect[i].set_color(brick.get_color());
        drop_effect[i].set_max_time(0.5);
        drop_effect[i].reset();
        drop_effect[i].update();
    }

    bottom_collision = true;
    fast_drop = true;
    effect_timer.restart();
    set_brick(brick);
}

void Field::movement_collision(
        sf::Vector2i& dxdy, const sf::Vector2i current_pos[4]) noexcept
{
    double elapsed_time = auto_drop.getElapsedTime().asSeconds();

    if (dxdy.x == 1) {
        for (int i = 0; i < 4; i++) {
            if (fill_matrix[current_pos[i].y][current_pos[i].x + 1] == 1) {
                dxdy.x = 0;
                break;
            }
        }
    } else if (dxdy.x == -1) {
        for (int i = 0; i < 4; i++) {
            if (fill_matrix[current_pos[i].y][current_pos[i].x - 1] == 1) {
                dxdy.x = 0;
                break;
            }
        }
    }

    if (elapsed_time >= 0.6) {
        dxdy.y = 1;
        auto_drop.restart();
    }

    if (bottom_collision)
        dxdy.y = 0;
}

void Field::clear_and_move_brick(
        Brick& brick, const sf::Vector2i prev_pos[4]) noexcept
{
    // clear prev_pos
    for (int i = 0; i < 4; i++) {
        fill_matrix[prev_pos[i].y][prev_pos[i].x] = 0;
        matrix[prev_pos[i].y][prev_pos[i].x].setFillColor(
                sf::Color::Transparent);
        matrix[prev_pos[i].y][prev_pos[i].x].setOutlineThickness(1);
        matrix[prev_pos[i].y][prev_pos[i].x].setOutlineColor(
                sf::Color(224, 224, 224, 255 / 4));
    }

    sf::Vector2i current_pos[4];
    brick.write_position(current_pos);

    sf::Color color = brick.get_color();
    for (int i = 0; i < 4; i++) {
        if (color == sf::Color::White) {
            matrix[current_pos[i].y][current_pos[i].x].setFillColor(
                    sf::Color::Transparent);
            matrix[current_pos[i].y][current_pos[i].x].setOutlineColor(
                    sf::Color(224, 224, 224, 255 / 4));
            matrix[current_pos[i].y][current_pos[i].x].setOutlineThickness(2);
        } else
            matrix[current_pos[i].y][current_pos[i].x].setFillColor(color);
    }
}
