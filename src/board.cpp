#include "board.h"
#include "utils.h"

Board::Board(unsigned width, unsigned height, unsigned bombCount)
    : width(width), height(height), bombCount(bombCount) {

    for (int i = 0; i <= 11; i++) {
        if (!tileTexture.loadFromFile("resources/images/tile" + std::to_string(i) + ".png"))
            throw std::runtime_error("Failed to load texture");

        textures.push_back(tileTexture);
    }

    build_tiles<Tile>(width, height, tiles, [](unsigned x, unsigned y) {
        return Tile{x, y};
    });

    placeBombs(bombCount, width, height); 
    calculateAdjacency();
}

void Board::revealTile(unsigned x, unsigned y) {
    auto& t = tileAt(x, y);
    //std::this_thread::sleep_for(std::chrono::milliseconds(20)); TODO make it so not all tiles are revealed instantly, instead like wave
    if (!t.revealed && t.currState != 11) {
        if (t.state == 0) {
            t.currState = 10;
            t.revealed = true;

            for (int dy = -1; dy <= 1; ++dy) {
                for (int dx = -1; dx <= 1; ++dx) {
                    if (dx == 0 && dy == 0) {
                        continue;
                    }

                    int nx = static_cast<int>(x) + dx;
                    int ny = static_cast<int>(y) + dy;

                    if (nx < 0 || ny < 0 ||
                        nx >= static_cast<int>(width) ||
                        ny >= static_cast<int>(height)) {
                        continue;
                    }

                    auto& n = tileAt(static_cast<unsigned>(nx), static_cast<unsigned>(ny));
                    if (n.state < 9) {
                        revealTile(static_cast<unsigned>(nx), static_cast<unsigned>(ny));
                    }
                }
            }
        }
        if (t.state > 0 &&t.state < 9)
        {
            t.currState = t.state;
            t.revealed = true;
        }
        if (t.state == 9) {
            // TODO fix game over
            /*while (1 == 1) {
                std::cout << "YOU LOSE NOOB ";
            }*/
           t.currState = t.state;
           t.revealed = true;
        }
    }
}

void Board::placeFlag(unsigned x, unsigned y) {
    auto& t = tileAt(x, y);
    if (t.currState == 11) {
        t.currState = 0;
    }
    else if (t.currState == 0) {
        t.currState = 11;
    }

}

void Board::placeBombs(unsigned bombCount, unsigned width, unsigned height) {
    for (unsigned i = 0; i < bombCount; i++) {
        auto [x, y] = random_coord(width, height);
        tileAt(x, y).state = 9;
    }
}

Tile& Board::tileAt(unsigned x, unsigned y) {
    return tiles[y * width + x];
}

void Board::calculateAdjacency() {
    for (const auto& tile : tiles) {
        if (tile.state != 9) {
            continue;
        }

        for (int dy = -1; dy <= 1; dy++) {
            for (int dx = -1; dx <= 1; dx++) {
                if (dx == 0 && dy == 0) {
                    continue;
                }

                int tx = static_cast<int>(tile.x) + dx;
                int ty = static_cast<int>(tile.y) + dy;

                if (tx < 0 || tx >= static_cast<int>(width) ||
                    ty < 0 || ty >= static_cast<int>(height)) {
                    continue;
                }

                auto& t = tileAt(static_cast<unsigned>(tx), static_cast<unsigned>(ty));
                if (t.state != 9) {
                    t.state++;
                }
            }
        }
    }
}

void Board::render(sf::RenderWindow& window) {
    sf::Sprite sprite;
    for (const auto& tile : tiles) {
        sprite.setTexture(textures[tile.currState]);
        sprite.setScale(TILE_SIZE / sprite.getLocalBounds().width, TILE_SIZE / sprite.getLocalBounds().height);
        sprite.setPosition(tile.x*TILE_SIZE, tile.y*TILE_SIZE);
        window.draw(sprite);
    }
}

void Board::handleEvents(const sf::Event& event) {
    if (event.type != sf::Event::MouseButtonPressed) {
        return;
    }

    unsigned tx = static_cast<unsigned>(event.mouseButton.x / TILE_SIZE);
    unsigned ty = static_cast<unsigned>(event.mouseButton.y / TILE_SIZE);

    if (tx >= width || ty >= height) {
        return;
    }

    if (event.mouseButton.button == sf::Mouse::Left) {
        revealTile(tx, ty);
    } else if (event.mouseButton.button == sf::Mouse::Right) {
        placeFlag(tx, ty);
    }
}