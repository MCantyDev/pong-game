#ifndef STATEMANAGER_H
#define STATEMANAGER_H

class State; // Forward Declare State to stop Circular dependency
class InputManager;

// SMFL Includes
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

// Standard Library Includes
#include <iostream>

/**
 * @class StateManager
 * @brief Manages the states of the game.
 *
 * The StateManager ensures that state transitions follow a logical pattern,
 * such as Menu -> Playing, Playing -> Paused, and prevents invalid transitions
 * (e.g., Menu -> Paused).
 *
 * The manager handles the current state and ensures smooth transitions
 * between states, making sure game logic is properly handled at all times.
 */
class StateManager
{
public:
	~StateManager();
	static StateManager* GetInstance();

	// State Specific Functions - Each State will handle Input, Update and Render differently
	void handleInput();
	void update();
	void render();

	static void ChangeState(State* newState);
	static State* GetState();

private:
	StateManager();
	static StateManager* instance;
	static State* state;

	static sf::Clock swapClock;
	static bool canAction;
	static float debounceTime;
};

#endif // STATEMANAGER_H