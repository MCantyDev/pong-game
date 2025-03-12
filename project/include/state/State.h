#ifndef STATE_H
#define STATE_H

#include "StateManager.h"

/*
* @class State
* @brief Abstract Class State - Parent of all States within Application
* 
* Current State Plan - MenuState, PlayingState, PausedState, SettingState, GameOverState
*/
class State
{
public:
	State(StateManager* manager) 
		: stateManager(manager) {};

	virtual ~State() = default;

	virtual void handleInput() = 0;
	virtual void update() = 0;
	virtual void render() = 0;

protected:
	StateManager* stateManager;
};

#endif // STATE_H