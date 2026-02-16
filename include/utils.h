#pragma once
#include <utility>
#include <vector>

std::pair<unsigned, unsigned> random_coord(unsigned width, unsigned height);

template <typename Tile, typename Factory>
void build_tiles(unsigned width, unsigned height, std::vector<Tile>& out, Factory make_tile) {
    out.clear();
    out.reserve(width * height);

    for (unsigned y = 0; y < height; ++y) {
        for (unsigned x = 0; x < width; ++x) {
            out.push_back(make_tile(x, y));
        }
    }
}