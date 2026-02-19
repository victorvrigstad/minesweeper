#include "path_board.h"
#include "utils.h"
#include <array>
#include <algorithm>
#include <cmath>
 
PathBoard::PathBoard(unsigned width, unsigned height, unsigned obstacleCount)
    : width(width), height(height) {
    for (int i = 0; i <= 14; ++i) {
        if (!tileTexture.loadFromFile("resources/images/tile" + std::to_string(i) + ".png")) {
            throw std::runtime_error("Failed to load texture");
        }
        textures.push_back(tileTexture);
    }
    
        build_tiles<PathTile>(width, height, tiles, [](unsigned x, unsigned y) {
        return PathTile{x, y, false};
    });

    generateObstacles(obstacleCount);
}

PathTile& PathBoard::tileAt(unsigned x, unsigned y) {
    return tiles[y * width + x];
}

void PathBoard::generateObstacles(unsigned obstacleCount) {
    for (unsigned i = 0; i < obstacleCount; ++i) {
        auto [x, y] = random_coord(width, height);
        tileAt(x, y).isObstacle = true;
    }
}

void PathBoard::placeStart(PathTile& t) {
    startTile = t;
}

void PathBoard::placeEnd(PathTile& t) {
    endTile = t;
}

void PathBoard::render(sf::RenderWindow& window) {
    sf::Sprite sprite;
    for (const auto& tile : tiles) {
        int drawState = 0;
        if (hasStart && tile == startTile) {
            drawState = 12;
        } else if (hasEnd && tile == endTile) {
            drawState = 13;
        } else if (tile.isPath) {
            drawState = 14;
        } else if (tile.visited) {
            //drawState = 1;
        } else if (tile.isObstacle) {
            drawState = 10;
        }

        sprite.setTexture(textures[drawState]);
        sprite.setScale(
            TILE_SIZE / sprite.getLocalBounds().width,
            TILE_SIZE / sprite.getLocalBounds().height
        );
        sprite.setPosition(tile.x * TILE_SIZE, tile.y * TILE_SIZE);
        window.draw(sprite);
    }
}

void PathBoard::handleEvents(const sf::Event& event) {
     if (event.type != sf::Event::MouseButtonPressed) {
        return;
    }

    unsigned tx = static_cast<unsigned>(event.mouseButton.x / TILE_SIZE);
    unsigned ty = static_cast<unsigned>(event.mouseButton.y / TILE_SIZE);

    if (tx >= width || ty >= height) {
        return;
    }

    auto& clickedTile = tileAt(tx, ty);
    if (event.mouseButton.button == sf::Mouse::Left) {
        placeStart(clickedTile);
        hasStart = true;
    } else if (event.mouseButton.button == sf::Mouse::Right) {
        placeEnd(clickedTile);
        hasEnd = true;
    }

    if (hasStart && hasEnd) {
        clearSearchState();
        bestFirstSearch(tileAt(startTile.x, startTile.y), tileAt(endTile.x, endTile.y));
    }
}

void PathBoard::clearSearchState() {
    for (auto& t : tiles) {
        t.visited = false;
        t.isPath = false;
    }
}
// Normal DFS exploring neighboring tiles in a fixed order
bool PathBoard::depthFirstSearch(PathTile& currentTile, PathTile& endTile) {
    if (currentTile.isObstacle || currentTile.visited)
        return false;

    currentTile.visited = true;

    if (currentTile == endTile) {
        currentTile.isPath = true;
        return true;
    }

    static const std::array<std::pair<int,int>, 4> dirs = {{
        {1, 0}, {-1, 0}, {0, 1}, {0, -1}
    }};

    for (const auto& [dx, dy] : dirs) {
        int nx = static_cast<int>(currentTile.x) + dx;
        int ny = static_cast<int>(currentTile.y) + dy;

        if (nx < 0 || ny < 0 ||
            nx >= static_cast<int>(width) ||
            ny >= static_cast<int>(height)) {
            continue;
        }

        PathTile& next = tileAt(static_cast<unsigned>(nx), static_cast<unsigned>(ny));

        if (depthFirstSearch(next, endTile)) {
            currentTile.isPath = true;
            return true;
        }
    }
    return false;
}
// BestFirstSearch - Manhattan-guided DFS: works by computing the Manhattan distance 
// from each neighboring tile to the target and exploring the neighbors with 
// the smallest distance first. It prioritizes paths that appear closer to the goal.
bool PathBoard::bestFirstSearch(PathTile& currentTile, PathTile& endTile) {
    if (currentTile.isObstacle || currentTile.visited)
        return false;

    currentTile.visited = true;

    if (currentTile == endTile) {
        currentTile.isPath = true;
        return true;
    }

    std::array<std::pair<int,int>, 4> dirs = {{{1,0}, {-1,0}, {0,1}, {0,-1}}};

    auto manhattan = [&](int x, int y) {
        return std::abs(x - static_cast<int>(endTile.x)) +
            std::abs(y - static_cast<int>(endTile.y));
    };

    // sort directions so closest-to-end neighbor is tried first
    std::sort(dirs.begin(), dirs.end(), [&](const auto& a, const auto& b) {
        int ax = static_cast<int>(currentTile.x) + a.first;
        int ay = static_cast<int>(currentTile.y) + a.second;
        int bx = static_cast<int>(currentTile.x) + b.first;
        int by = static_cast<int>(currentTile.y) + b.second;
        return manhattan(ax, ay) < manhattan(bx, by);
    });

    for (const auto& [dx, dy] : dirs) {
        int nx = static_cast<int>(currentTile.x) + dx;
        int ny = static_cast<int>(currentTile.y) + dy;

        if (nx < 0 || ny < 0 ||
            nx >= static_cast<int>(width) ||
            ny >= static_cast<int>(height)) {
            continue;
        }

        PathTile& next = tileAt(static_cast<unsigned>(nx), static_cast<unsigned>(ny));

        if (bestFirstSearch(next, endTile)) {
            currentTile.isPath = true;
            return true;
        }
    }
    return false;
}