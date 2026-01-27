#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "constants.h"

struct Tile {
    unsigned x;
    unsigned y;
    bool flagged = false;
    bool revealed = false;

    int state = 0; // 0-8 = adjacent bombs & 9 = bomb
};

class Board {
public:
    Board(unsigned width, unsigned height, unsigned bombCount);
    void render(sf::RenderWindow& window);

private:
    void placeBombs(int bombs);
    void calculateAdjacency();
    unsigned width;
    unsigned height;
    unsigned bombCount;
    std::vector<Tile> tiles;
    sf::Texture tileTexture;
};