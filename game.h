#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

struct Tile {
    int x;
    int y;
    bool flagged = false;
    bool revealed = false;

    int state = 0; // 0-8 = adjacent bombs & 9 = bomb
};


class Game {
public:
    Game(unsigned width, unsigned height, unsigned bombAmount);
    void run();

private:
    void handleEvents();
    void render();
    void placeBombs(int bombs);
    void calculateAdjacency();

    sf::RenderWindow window;

    int TILE_SIZE = 25;
    int gridWidth;
    int gridHeight;
    std::vector<Tile> tiles;
    sf::Texture tileTexture;
};