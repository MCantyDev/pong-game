#include "core/StateManager.h"

// Different State Types 
#include "state/State.h"
#include "state/MainMenuState.h"
#include "state/PlayingState.h"

// Definition of InputManager
#include "command/InputManager.h"

StateManager* StateManager::instance = nullptr;
State* StateManager::state = nullptr;

sf::Clock StateManager::swapClock = sf::Clock();
bool StateManager::canAction = false;
float StateManager::debounceTime = 1.f;

StateManager::StateManager()
{
	state = new MainMenuState();
	InputManager::InitialiseBindingsForState();
}

StateManager::~StateManager()
{
	if (state)
	{
		delete state;
		state = nullptr;
	}
}

StateManager* StateManager::GetInstance()
{
	if (!instance)
		instance = new StateManager();

	return instance;
}

void StateManager::ChangeState(State* newState)
{
	if (canAction && state != newState)
	{

		delete state;
		state = newState;
		
		InputManager::InitialiseBindingsForState();

		swapClock.restart();
		canAction = false;
	}

	if (swapClock.getElapsedTime().asSeconds() >= debounceTime)
	{
		canAction = true;
	}
}

State* StateManager::GetState()
{
	return state;
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