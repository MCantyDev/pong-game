#ifndef PLAYINGSTATE_H
#define PLAYINGSTATE_H

#include "state/State.h"

/*
* @class PlayingState
* @brief Playing State of the Game - Signifies the User is playing the Game
* 
* Playing State will give user access to Paused State
*/
class PlayingState : public State
{
public:
	PlayingState();
	~PlayingState();

private:
};

#endif // PLAYINGSTATE_H