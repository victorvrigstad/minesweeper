#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "constants.h"

struct PathTile {
    unsigned x;
    unsigned y;

    bool isObstacle = false;
    bool visited = false;
    bool isPath = false;

    bool operator==(const PathTile& other) const {
    return x == other.x && y == other.y;
    }
    bool operator!=(const PathTile& other) const {
        return !(*this == other);
    }
};



class PathBoard {
public:
    PathBoard(unsigned width, unsigned height, unsigned obstacleCount);
    void render(sf::RenderWindow& window);
    void handleEvents(const sf::Event& event);
    void stepDfs();

private:
    void generateObstacles(unsigned obstacleCount);
    PathTile& tileAt(unsigned x, unsigned y);
    void placeStart(PathTile& t);
    void placeEnd(PathTile& t);

    
    bool depthFirstSearch(PathTile& startTile, PathTile& endTile);
    bool bestFirstSearch(PathTile& startTile, PathTile& endtile);
    
    
    void beginSearch();
    void clearSearchState();

    unsigned width;
    unsigned height;
    PathTile startTile;
    PathTile endTile;
    bool hasStart = false;
    bool hasEnd = false;
    std::vector<PathTile> tiles;
    bool searchRunning = false;
    bool searchFound = false;
    std::vector<int> stack;
    
    sf::Texture tileTexture;
    std::vector<sf::Texture> textures;
};
