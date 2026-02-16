#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "constants.h"

struct PathTile {
    unsigned x;
    unsigned y;
    bool obstacle = false;
};

class PathBoard {
public:
    PathBoard(unsigned width, unsigned height, unsigned obstacleCount);
    void render(sf::RenderWindow& window);

private:
    void generateObstacles(unsigned obstacleCount);
    PathTile& tileAt(unsigned x, unsigned y);

    unsigned width;
    unsigned height;
    std::vector<PathTile> tiles;
    
    sf::Texture tileTexture;
    std::vector<sf::Texture> textures;
};