#ifndef STATE_H
#define STATE_H

#include "core/StateManager.h"

/*
* @class State
* @brief Abstract Class State - Parent of all States within Application
* 
* Current State Plan - MenuState, PlayingState, PausedState, SettingState, GameOverState
*/
class State
{
public:
	State() = default;

	virtual ~State() = default;

	virtual void update() = 0;
	virtual void render() = 0;

	// Commands
	virtual void PlayerOneMoveUp() = 0;
	virtual void PlayerOneMoveDown() = 0;
	virtual void PlayerTwoMoveUp() = 0;
	virtual void PlayerTwoMoveDown() = 0;
	virtual void Pause() = 0;
	virtual void Select() = 0;
	virtual void Return() = 0;
};

#endif // STATE_H