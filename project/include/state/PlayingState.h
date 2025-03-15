#ifndef PLAYINGSTATE_H
#define PLAYINGSTATE_H

#include "state/State.h"
#include "DeltaTimeClock.h"
#include "RenderWindowManager.h"

// Drawable Include
#include "drawables/Paddle.h"
#include "drawables/AIPaddle.h"
#include "drawables/Ball.h"

// SMFML Include
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"

// Standard Library Include
#include <random>
#include <cmath>
#include <memory>

/*
* @class PlayingState
* @brief Playing State of the Game - Signifies the User is playing the Game
* 
* Playing State will give user access to Paused State
*/
class PlayingState : public State
{
public:
	PlayingState(StateManager* manager);
	~PlayingState();

	virtual void handleInput() override;
	virtual void update() override;
	virtual void render() override;
private:
	// Private Functions
	void initialiseSounds();		// Loads Sounds from Files

	// Paddle Values
	Paddle* playerOne = nullptr;
	Paddle* playerTwo = nullptr;

	// AI Paddle Values
	AiPaddle* aiPaddle = nullptr;

	// Ball Values
	Ball* ball = nullptr;
};

#endif // PLAYINGSTATE_H