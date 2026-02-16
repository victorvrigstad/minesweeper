#pragma once
#include <SFML/Graphics.hpp>
#include "board.h"
#include <memory>
#include "state.h"

class Game {
public:
    Game(unsigned width, unsigned height);
    void run();

private:
    void handleEvents();
    void render();

    std::map<int, std::unique_ptr<State>> states;
    int current_state = MENU_STATE;
    sf::RenderWindow window;
    //Board board;
};