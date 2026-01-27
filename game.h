#pragma once
#include <SFML/Graphics.hpp>
#include "board.h"

class Game {
public:
    Game(unsigned width, unsigned height);
    void run();

private:
    void handleEvents();
    void render();

    sf::RenderWindow window;
    Board board;
};