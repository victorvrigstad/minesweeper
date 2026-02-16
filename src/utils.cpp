#include "utils.h"
#include <random>

std::pair<unsigned, unsigned> random_coord(unsigned width, unsigned height) {
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<unsigned> xDist(0, width - 1);
    std::uniform_int_distribution<unsigned> yDist(0, height - 1);
    return {xDist(rng), yDist(rng)};
}