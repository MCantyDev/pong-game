#ifndef COMMANDS_H
#define COMMANDS_H

/**
 * @file Commands.h
 * @brief Defines concrete Command classes used by the InputManager to process player inputs in different game states.
 *
 * Each Command subclass encapsulates a specific input action, forwarding the request to the current game state.
 */
#include "Command/Command.h"
#include "state/State.h"

/**
 * @class PlayerOneMoveUp
 * @brief Command to move Player One's paddle up.
 */
class PlayerOneMoveUp : public Command
{
public:
	PlayerOneMoveUp(State *currentState) : Command(currentState) {}

	/**
	 * @brief Executes the Player One move up action by delegating to the current state.
	 */
	virtual void execute() override
	{
		if (state)
			state->PlayerOneMoveUp();
	}
};

/**
 * @class PlayerOneMoveDown
 * @brief Command to move Player One's paddle down.
 */
class PlayerOneMoveDown : public Command
{
public:
	PlayerOneMoveDown(State *currentState) : Command(currentState) {}

	/**
	 * @brief Executes the Player One move down action by delegating to the current state.
	 */
	virtual void execute() override
	{
		if (state)
			state->PlayerOneMoveDown();
	}
};

/**
 * @class PlayerTwoMoveUp
 * @brief Command to move Player Two's paddle up.
 */
class PlayerTwoMoveUp : public Command
{
public:
	PlayerTwoMoveUp(State *currentState) : Command(currentState) {}

	/**
	 * @brief Executes the Player Two move up action by delegating to the current state.
	 */
	virtual void execute() override
	{
		if (state)
			state->PlayerTwoMoveUp();
	}
};

/**
 * @class PlayerTwoMoveDown
 * @brief Command to move Player Two's paddle down.
 */
class PlayerTwoMoveDown : public Command
{
public:
	PlayerTwoMoveDown(State *currentState) : Command(currentState) {}

	/**
	 * @brief Executes the Player Two move down action by delegating to the current state.
	 */
	virtual void execute() override
	{
		if (state)
			state->PlayerTwoMoveDown();
	}
};

/**
 * @class Pause
 * @brief Command to pause the game.
 */
class Pause : public Command
{
public:
	Pause(State *currentState) : Command(currentState) {}

	/**
	 * @brief Executes the pause action by delegating to the current state.
	 */
	virtual void execute() override
	{
		if (state)
			state->Pause();
	}
};

/**
 * @class Select
 * @brief Command to select an option in the game menu or UI.
 */
class Select : public Command
{
public:
	Select(State *currentState) : Command(currentState) {}

	/**
	 * @brief Executes the select action by delegating to the current state.
	 */
	virtual void execute() override
	{
		if (state)
			state->Select();
	}
};

/**
 * @class Return
 * @brief Command to return or go back in the game menu or UI.
 */
class Return : public Command
{
public:
	Return(State *currentState) : Command(currentState) {}

	/**
	 * @brief Executes the return action by delegating to the current state.
	 */
	virtual void execute() override
	{
		if (state)
			state->Return();
	}
};

#endif // COMMANDS_H