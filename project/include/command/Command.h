#ifndef COMMAND_H
#define COMMAND_H

#include "state/State.h"

/**
 * @class Command
 * @brief Abstract base class representing a user input command in the Pong game.
 *
 * Commands encapsulate specific input actions tied to the game's current state.
 * They are used by the input manager to execute player actions such as moving paddles.
 */
class Command
{
public:
	/**
	 * @brief Constructs a Command with a reference to the current game state.
	 * @param currentState Pointer to the current State object.
	 */
	Command(State *currentState) : state(currentState) {}

	/**
	 * @brief Virtual destructor for proper cleanup in derived classes.
	 */
	virtual ~Command() = default;

	/**
	 * @brief Executes the command corresponding to a player input.
	 *
	 * Must be overridden by subclasses to implement specific input actions.
	 */
	virtual void execute() = 0;

protected:
	State *state;
};

#endif // COMMAND_H