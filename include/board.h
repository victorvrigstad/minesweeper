#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "constants.h"

struct Tile {
    unsigned x;
    unsigned y;
    bool flagged = false;
    bool revealed = false;
    int currState = 0;
    int state = 0; // 0-8 = adjacent bombs, 9 = bomb, 10 = discovered & 11 = flag
};

class Board {
public:
    Board(unsigned width, unsigned height, unsigned bombCount);
    void render(sf::RenderWindow& window);
    void handleEvents(const sf::Event& event);
    void revealTile(unsigned x, unsigned y);
    void placeFlag(unsigned x, unsigned y);

private:
    void placeBombs(unsigned bombs, unsigned width, unsigned height);
    void calculateAdjacency();
    unsigned width;
    unsigned height;
    unsigned bombCount;
    std::vector<Tile> tiles;
    sf::Texture tileTexture;
    std::vector<sf::Texture> textures;
    std::vector<std::pair<unsigned, unsigned>> bombPlacement;
    Tile& tileAt(unsigned x, unsigned y);
};