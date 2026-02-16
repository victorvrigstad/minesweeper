#include "menu_state.h"

MenuState::MenuState(unsigned width, unsigned height) {
    background.setSize(sf::Vector2f(static_cast<float>(width), static_cast<float>(height)));
    background.setFillColor(sf::Color(30, 40, 70));

    auto setup_button = [](sf::RectangleShape& b, float x, float y, sf::Color color) {
        b.setSize(sf::Vector2f(240.f, 70.f));
        b.setOrigin(b.getSize().x / 2.f, b.getSize().y / 2.f);
        b.setPosition(x, y);
        b.setFillColor(color);
    };

    float cx = width / 2.f;
    setup_button(easy_button,   cx, height * 0.35f, sf::Color(70, 170, 90));   // green
    setup_button(medium_button, cx, height * 0.50f, sf::Color(220, 180, 60));  // yellow
    setup_button(hard_button,   cx, height * 0.65f, sf::Color(180, 70, 70));   // red
}

void MenuState::handle_event(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P) {
        next_state = PATHFIND_STATE;
        return;
    }
    
    if (event.type != sf::Event::MouseButtonPressed ||
        event.mouseButton.button != sf::Mouse::Left) {
        return;
    }

    sf::Vector2f mouse(static_cast<float>(event.mouseButton.x),
                       static_cast<float>(event.mouseButton.y));

    if (easy_button.getGlobalBounds().contains(mouse)) {
        selected = Difficulty::Easy;
        next_state = GAME_STATE;
    } else if (medium_button.getGlobalBounds().contains(mouse)) {
        selected = Difficulty::Medium;
        next_state = GAME_STATE;
    } else if (hard_button.getGlobalBounds().contains(mouse)) {
        selected = Difficulty::Hard;
        next_state = GAME_STATE;
    }
    
}

void MenuState::render(sf::RenderTarget& target) {
    target.draw(background);
    target.draw(easy_button);
    target.draw(medium_button);
    target.draw(hard_button);
}

int MenuState::get_next_state() {
    int out = next_state;
    next_state = MENU_STATE;
    return out;
}

Difficulty MenuState::get_selected_difficulty() const {
    return selected;
}