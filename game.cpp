#include "game.h"
#include <iostream>

Game::Game(unsigned width, unsigned height)
    : window(sf::VideoMode(width, height), "Test"),
    board(width/TILE_SIZE, height/TILE_SIZE, DEFAULT_BOMBS) {
        window.setFramerateLimit(FPS); //without this, 100% gpu and fps over 9000 
}

void Game::run() {
    while (window.isOpen()) {
        handleEvents();
        window.clear();
        render();
        window.display();
    }
}

void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left) {
                auto m = sf::Mouse::getPosition(window);
                board.revealTile(m.x/TILE_SIZE, m.y/TILE_SIZE);
            }
        if (event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Right)  {
                auto m = sf::Mouse::getPosition(window);
                board.placeFlag(m.x/TILE_SIZE, m.y/TILE_SIZE);
            }
    }
}

void Game::render() {
   board.render(window);
}