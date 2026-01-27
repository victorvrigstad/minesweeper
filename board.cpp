#include "board.h"

Board::Board(unsigned width, unsigned height, unsigned bombCount)
    : width(width), height(height), bombCount(bombCount) {

    if (!tileTexture.loadFromFile("images/51230.png"))
        throw std::runtime_error("Failed to load texture");

    for (unsigned y = 0; y < height; y++){
        for (unsigned x = 0; x < width; x++){
            tiles.push_back(Tile{x, y});
        }
    }

    //placeBombs(bombAmount); //TODO
    //calculateAdjacency();
}

void Board::render(sf::RenderWindow& window) {
    sf::Sprite sprite;
    sprite.setTexture(tileTexture);
    sprite.setScale(TILE_SIZE / sprite.getLocalBounds().width, TILE_SIZE / sprite.getLocalBounds().height);
    for (Tile tile : tiles) {
        sprite.setPosition(tile.x*TILE_SIZE, tile.y*TILE_SIZE);
        window.draw(sprite);
    }
}