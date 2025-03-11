#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "state/State.h"

/*
* @class MenuState
* @brief Menu State of the Game - Signifies the User is at the Main Menu of the Game
* 
* Menu State will give user access to playing state and settings state
*/
class MenuState : public State
{
public:
	MenuState();
	~MenuState();

private:
};

#endif // MENUSTATE_H