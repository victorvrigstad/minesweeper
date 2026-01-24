#include "game.h"
#include <iostream>

Game::Game(unsigned width, unsigned height)
    : window(sf::VideoMode(width, height), "Test") {
    gridWidth  = width  / TILE_SIZE;
    gridHeight = height / TILE_SIZE;

    if (!tileTexture.loadFromFile("images/51230.png")) {
        throw std::runtime_error("Failed to load texture");
    }

    for (int y = 0; y < gridHeight; y++){
        for (int x = 0; x < gridWidth; x++){
            tiles.push_back(Tile{x, y});
        }
    }
    window.setFramerateLimit(60);
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
                std::cout << m.x << ":" << m.y << std::endl;
            }  
    }
}

void Game::render() {
    sf::Sprite sprite;
    sprite.setTexture(tileTexture);
    sprite.setScale(TILE_SIZE / sprite.getLocalBounds().width, TILE_SIZE / sprite.getLocalBounds().height);
    for (Tile tile : tiles) {
        sprite.setPosition(tile.x*TILE_SIZE, tile.y*TILE_SIZE);
        window.draw(sprite);
    }
}