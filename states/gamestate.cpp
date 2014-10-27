#include <states/gamestate.hpp>

GameState::GameState(StateStack &stack, Context context) :
    State(stack, context)
{
}


void GameState::draw()
{
}

bool GameState::update(sf::Time dt)
{
    return true;
}

bool GameState::handleEvent(const sf::Event& event)
{
    return true;
}
