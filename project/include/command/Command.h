#ifndef COMMAND_H
#define COMMAND_H

#include "state/State.h"

class Command
{
public:
	Command(State* currentState) : state(currentState) {}
	virtual ~Command() = default;

	virtual void execute() = 0;

protected:
	State* state;
};

#endif // COMMAND_H