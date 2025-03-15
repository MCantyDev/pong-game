#include "StateManager.h"

// Different State Types 
#include "state/State.h"
#include "state/MenuState.h"
#include "state/PlayingState.h"

StateManager::StateManager()
	: state(new MenuState(this))
{
	std::cout << "Setup: State Manager Initialised" << std::endl;
}

StateManager::~StateManager()
{
	if (state)
	{
		delete state;
		state = nullptr;
	}
	std::cout << "Closing: State Manager Closed" << std::endl;
}

void StateManager::changeState(State* newState)
{
	if (canAction && state != newState)
	{

		delete state;
		state = newState;
		
		swapClock.restart();
		canAction = false;
	}

	if (swapClock.getElapsedTime().asSeconds() >= debounceTime)
	{
		canAction = true;
	}
}

void StateManager::handleInput()
{
	if (state)
	{
		state->handleInput();
	}
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