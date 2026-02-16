#pragma once
#include "state.h"
#include "path_board.h"

class PathfindingState : public State {
public:
    PathfindingState(unsigned cols, unsigned rows, unsigned obstacles);
    void handle_event(const sf::Event& event) override;
    void render(sf::RenderTarget& target) override;
    int get_next_state() override;

private:
    int next_state = PATHFIND_STATE;
    PathBoard board;
};