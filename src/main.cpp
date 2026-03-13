#include <ncurses.h>
#include <thread>
#include <chrono>
#include "game/game.h"


void draw(const Game& game) {
    clear();
    
    const auto& snake = game.getSnake();
    Point food = game.getFood();
    int score = game.getScore();

    for (size_t x{0}; x < WIDTH + 2; ++x) {
        mvprintw(0, x, "#");
        mvprintw(HEIGHT + 1, x, "#");
    }

    for (size_t y{0}; y < HEIGHT + 2; ++y) {
        mvprintw(y, 0, "#");
        mvprintw(y, WIDTH + 1, "#");
    }

    mvprintw(food.y + 1, food.x + 1, "@");

    for (size_t i{0}; i < snake.size(); ++i) {
        char s = (i == 0) ? '0' : 'o';
        mvprintw(snake[i].y + 1, snake[i].x + 1, "%c", s);
    }

    mvprintw(HEIGHT + 3, 0, "Score: %d", score);
    
    refresh();

}


int main() {

    initscr();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    Game game;
    Direction curDir = Direction::RIGHT;
    bool running = true;

    while (running && !game.isGameOver()) {
        int ch = getch();

        switch(ch) {
            case 'w': curDir = Direction::UP; break;
            case 's': curDir = Direction::DOWN; break;
            case 'a': curDir = Direction::LEFT; break;
            case 'd': curDir = Direction::RIGHT; break;
            case 'q': running = false; break;
        }

        game.step(curDir);

        draw(game);

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    nodelay(stdscr, FALSE);
    refresh();
    getch();

    endwin();
    
    return 0;
}