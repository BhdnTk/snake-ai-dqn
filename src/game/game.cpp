#include "game.h"
#include <cstdlib>
#include <ctime>

Game::Game() {
    srand(static_cast<unsigned int>(time(nullptr)));
    reset();
}

void Game::reset() {

    snake.clear();

    snake.push_back({WIDTH / 2, HEIGHT / 2});
    snake.push_back({WIDTH / 2 - 1, HEIGHT / 2});
    snake.push_back({WIDTH / 2 - 2, HEIGHT / 2});

    direction = Direction::RIGHT;
    game_over = false;
    score = 0;

    spawnFood();
}

void Game::spawnFood() {

    while (true) {

        int x = rand() % WIDTH;
        int y = rand() % HEIGHT;

        bool onSnake = false;
        for (const auto &s : snake) {
            if (s.x == x && s.y == y) {
                onSnake = true;
                break;
            }
        }

        if (!onSnake) {
            food = {x, y};
            return;
        }

    }
}

float Game::step(Direction dir) {

    if (game_over) return 0.0f;

    if ((direction == Direction::UP && dir != Direction::DOWN) ||
        (direction == Direction::LEFT && dir != Direction::RIGHT) ||
        (direction == Direction::RIGHT && dir != Direction::LEFT) ||
        (direction == Direction::DOWN && dir != Direction::UP)) {

        direction = dir;
        
    }

    Point head = snake.front();

    switch (direction) {
    case Direction::UP:
        head.y--;
        break;
    case Direction::DOWN:
        head.y++;
        break;
    case Direction::LEFT:
        head.x--;
        break;
    case Direction::RIGHT:
        head.x++;
        break;
    }

    if ((head.x < 0 || head.x >= WIDTH) ||
        (head.y < 0 || head.y >= HEIGHT)) {
        game_over = true;
        return -10.0f;
    }

    for (const auto &s : snake) {
        if (s == head) {
            game_over = true;
            return -10.0f;
        }
    }

    snake.insert(snake.begin(), head);

    if (head == food) {
        ++score;
        spawnFood();
        return 10.0f;
    }
    else {
        snake.pop_back();
        return -0.1f;
    }
}

const std::vector<Point> &Game::getSnake() const { return snake; }

const Point &Game::getFood() const { return food; }

bool Game::isGameOver() const { return game_over; }

int Game::getScore() const { return score; }