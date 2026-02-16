#include "path_board.h"
#include "utils.h"
 
PathBoard::PathBoard(unsigned width, unsigned height, unsigned obstacleCount)
    : width(width), height(height) {
    for (int i = 0; i <= 11; ++i) {
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
        tileAt(x, y).obstacle = true;
    }
}

void PathBoard::render(sf::RenderWindow& window) {
    sf::Sprite sprite;
    for (const auto& tile : tiles) {
        int drawState = tile.obstacle ? 9 : 0;

        sprite.setTexture(textures[drawState]);
        sprite.setScale(
            TILE_SIZE / sprite.getLocalBounds().width,
            TILE_SIZE / sprite.getLocalBounds().height
        );
        sprite.setPosition(tile.x * TILE_SIZE, tile.y * TILE_SIZE);
        window.draw(sprite);
    }
}