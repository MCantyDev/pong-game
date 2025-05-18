#ifndef COMMANDS_H
#define COMMANDS_H

#include "Command/Command.h"

#include "state/State.h"

/**
* Commands are the invidual commands used across the Pong game, the InputManager uses these commands to process functionality between game states.
*/

// Commands
class PlayerOneMoveUp : public Command
{
public:
	PlayerOneMoveUp(State* currentState) : Command(currentState) {}

	virtual void execute() override
	{
		if (state)
			state->PlayerOneMoveUp();
	}
};

class PlayerOneMoveDown : public Command
{
public:
	PlayerOneMoveDown(State* currentState) : Command(currentState) {}

	virtual void execute() override
	{
		if (state)
			state->PlayerOneMoveDown();
	}
};

class PlayerTwoMoveUp : public Command
{
public:
	PlayerTwoMoveUp(State* currentState) : Command(currentState) {}

	virtual void execute() override
	{
		if (state)
			state->PlayerTwoMoveUp();
	}
};

class PlayerTwoMoveDown : public Command
{
public:
	PlayerTwoMoveDown(State* currentState) : Command(currentState) {}

	virtual void execute() override
	{
		if (state)
			state->PlayerTwoMoveDown();
	}
};

class Pause : public Command
{
public:
	Pause(State* currentState) : Command(currentState) {}

	virtual void execute() override
	{
		if (state)
			state->Pause();
	}
};

class Select : public Command
{
public:
	Select(State* currentState) : Command(currentState) {}

	virtual void execute() override
	{
		if (state)
			state->Select();
	}
};

class Return : public Command
{
public:
	Return(State* currentState) : Command(currentState) {}

	virtual void execute() override
	{
		if (state)
			state->Return();
	}
};



#endif // COMMANDS_H