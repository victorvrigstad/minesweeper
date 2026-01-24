#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

struct Tile {
    int x;
    int y;
};


class Game {
public:
    Game(unsigned width, unsigned height);
    void run();

private:
    void handleEvents();
    void update();
    void render();

    sf::RenderWindow window;

    int TILE_SIZE = 25;
    int gridWidth;
    int gridHeight;
    std::vector<Tile> tiles;
    sf::Texture tileTexture;
};