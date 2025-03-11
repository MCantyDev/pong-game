#ifndef STATEMANAGER_H
#define STATEMANAGER_H

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
	StateManager();
	~StateManager();

private:

};

#endif // STATEMANAGER_H