#ifndef STATE_H
#define STATE_H

#include <SFML/Graphics.hpp>

constexpr int MENU_STATE   = 0;
constexpr int GAME_STATE   = 1;
constexpr int HIDDEN_STATE = 2;
//constexpr int EXIT_STATE   = -1;

enum class Difficulty {
    Easy,
    Medium,
    Hard
};

class State
{
public:
    virtual ~State() = default;
    virtual void handle_event(const sf::Event& event) = 0;
    virtual void render(sf::RenderTarget& target) = 0;
    virtual int get_next_state() = 0;
};

#endif 