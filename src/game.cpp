#include "game.h"
#include "constants.h"
#include "menu_state.h"
#include "game_state.h"
#include "pathfinding_state.h"
#include <iostream>


Game::Game(unsigned width, unsigned height)
    : window(sf::VideoMode(width, height), "Test") {
        window.setFramerateLimit(FPS); //without this, 100% gpu and fps over 9000 
        
        states.insert({MENU_STATE, std::make_unique<MenuState>(width, height)});
        current_state = MENU_STATE;
}

void Game::run() {
    while (window.isOpen()) {
        handleEvents();
        
        int next = states.at(current_state)->get_next_state();
        if (next != current_state) {
            if (current_state == GAME_STATE && next == MENU_STATE) {
                states.erase(GAME_STATE);

                constexpr unsigned MENU_W = 800;
                constexpr unsigned MENU_H = 600;
                window.create(sf::VideoMode(MENU_W, MENU_H), "Test");
                window.setFramerateLimit(FPS);

                states[MENU_STATE] = std::make_unique<MenuState>(MENU_W, MENU_H);
            }

        if (current_state == MENU_STATE && next == GAME_STATE) {
            auto* menu = dynamic_cast<MenuState*>(states.at(MENU_STATE).get());
            if (menu) {
                Difficulty d = menu->get_selected_difficulty();
                auto cfg = GameState::config_for(d);

                window.create(sf::VideoMode(cfg.cols * TILE_SIZE, cfg.rows * TILE_SIZE), "Test");
                window.setFramerateLimit(FPS);

                states[GAME_STATE] = std::make_unique<GameState>(d);
            }
        }
        if (current_state == MENU_STATE && next == PATHFIND_STATE) {
            constexpr unsigned COLS = 30, ROWS = 20, OBSTACLES = 120;
            window.create(sf::VideoMode(COLS * TILE_SIZE, ROWS * TILE_SIZE), "Pathfinding");
            window.setFramerateLimit(FPS);
            states[PATHFIND_STATE] = std::make_unique<PathfindingState>(COLS, ROWS, OBSTACLES);
        }

        if (current_state == PATHFIND_STATE && next == MENU_STATE) {
            states.erase(PATHFIND_STATE);
            constexpr unsigned MENU_W = 800, MENU_H = 600;
            window.create(sf::VideoMode(MENU_W, MENU_H), "Test");
            window.setFramerateLimit(FPS);
            states[MENU_STATE] = std::make_unique<MenuState>(MENU_W, MENU_H);
        } 
            current_state = next;
        }

        window.clear();
        render();
        window.display();
    }
}

void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
            return;
        }
        states.at(current_state)->handle_event(event);
    }
}

void Game::render() {
   states.at(current_state)->render(window);
}