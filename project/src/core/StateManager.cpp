#include "core/StateManager.h"

// Different State Types 
#include "state/State.h"
#include "state/MainMenuState.h"
#include "state/PlayingState.h"

// Definition of InputManager
#include "command/InputManager.h"

StateManager* StateManager::instance = nullptr;

std::unique_ptr<State> StateManager::state = nullptr;
std::unique_ptr<State> StateManager::nextState = nullptr;

bool StateManager::changeState = false;
sf::Clock StateManager::swapClock;
bool StateManager::canAction = true;
float StateManager::debounceTime = 1.f;

StateManager::StateManager()
{
	state = std::make_unique<MainMenuState>();
	InputManager::InitialiseBindingsForState();
}

StateManager::~StateManager()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

StateManager* StateManager::GetInstance()
{
	if (!instance)
		instance = new StateManager();

	return instance;
}

// Important Function which has a Debounce time to ensure States can be changed multiple times within a short span of time
void StateManager::SetChangeState(std::unique_ptr<State> newState)
{
    if (canAction && swapClock.getElapsedTime().asSeconds() >= debounceTime)
    {
        nextState = std::move(newState);
        changeState = true;
        swapClock.restart();
        canAction = false; 
    }
}

void StateManager::CheckStateChange()
{
    if (nextState && changeState)
    {
        state = std::move(nextState);
        InputManager::InitialiseBindingsForState();

		changeState = false;
		canAction = true; 
    }
}

State* StateManager::GetState()
{
	return state.get();
}

void StateManager::update()
{
	if (state)
	{
		state->update();
	}
}

void StateManager::render()
{
	if (state)
	{
		state->render();
	}
}