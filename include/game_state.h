#pragma once

#include "state.h"
#include "board.h"
#include "constants.h"

struct GameConfig {
    unsigned cols;
    unsigned rows;
    unsigned bombs;
};

class GameState : public State {
public:
    GameState(Difficulty difficulty);
    void handle_event(const sf::Event& event) override;
    void render(sf::RenderTarget& target) override;
    int get_next_state() override;
    static GameConfig config_for(Difficulty difficulty);

private:
    int next_state = GAME_STATE;
    Board board;
};