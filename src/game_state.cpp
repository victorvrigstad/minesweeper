#include "game_state.h"

GameConfig GameState::config_for(Difficulty difficulty) {
    switch (difficulty) {
        case Difficulty::Easy:   return {16, 12, 30};
        case Difficulty::Medium: return {24, 16, 70};
        case Difficulty::Hard:   return {30, 20, 120};
    }
    return {16, 12, 30};
}

GameState::GameState(Difficulty difficulty)
    : board(config_for(difficulty).cols,
            config_for(difficulty).rows,
            config_for(difficulty).bombs) {}

void GameState::handle_event(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        next_state = MENU_STATE;
        return;
    }

    board.handleEvents(event);
}

void GameState::render(sf::RenderTarget& target) {
    auto* window = dynamic_cast<sf::RenderWindow*>(&target);
    if (window) {
        board.render(*window);
    }
}

int GameState::get_next_state() {
    int out = next_state;
    next_state = GAME_STATE;
    return out;
}