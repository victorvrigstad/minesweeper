#include "pathfinding_state.h"

PathfindingState::PathfindingState(unsigned cols, unsigned rows, unsigned obstacles)
    : pathBoard(cols, rows, obstacles) {}

void PathfindingState::handle_event(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        next_state = MENU_STATE;
    }

    pathBoard.handleEvents(event);
}

void PathfindingState::render(sf::RenderTarget& target) {
    auto* window = dynamic_cast<sf::RenderWindow*>(&target);
    if (window) pathBoard.render(*window);
}

int PathfindingState::get_next_state() {
    int out = next_state;
    next_state = PATHFIND_STATE;
    return out;
}