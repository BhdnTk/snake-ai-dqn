#ifndef GAME_H
#define GAME_H

#include <vector>

struct Point {
    int x{};
    int y{};

    bool operator==(const Point&) const = default;
};

constexpr int WIDTH = 20;
constexpr int HEIGHT = 20;

enum class Direction {UP, DOWN, LEFT, RIGHT};


class Game {
    private: 
        std::vector<Point> snake;
        Point food;
        Direction direction;
        bool game_over;
        int score;  

        void spawnFood();

    public:
        Game();
        void reset();

        float step(Direction dir);

        const std::vector<Point>& getSnake() const;
        const Point& getFood() const;
        bool isGameOver() const;
        int getScore() const;
        std::vector<float> getState() const;

};
#endif