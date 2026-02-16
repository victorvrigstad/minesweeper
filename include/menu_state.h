#pragma once
#include "state.h"
#include <SFML/Graphics.hpp>

class MenuState : public State {
public:
    MenuState(unsigned width, unsigned height);
    void handle_event(const sf::Event& event) override;
    void render(sf::RenderTarget& target) override;
    int get_next_state() override;
    Difficulty get_selected_difficulty() const;

private:
    int next_state = MENU_STATE;
    Difficulty selected = Difficulty::Easy;

    sf::RectangleShape background;
    sf::RectangleShape easy_button;
    sf::RectangleShape medium_button;
    sf::RectangleShape hard_button;
};