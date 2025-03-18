#ifndef PLAYINGSTATE_H
#define PLAYINGSTATE_H

#include "state/State.h"
#include "GameEnums.h"

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
	PlayingState(GameMode mode);
	~PlayingState();

	virtual void update() override;
	virtual void render() override;

	// Command Overrides
	virtual void PlayerOneMoveUp() override;
	virtual void PlayerOneMoveDown() override;
	virtual void PlayerTwoMoveUp() override;
	virtual void PlayerTwoMoveDown() override;
	virtual void Pause() override;
	virtual void Select() override;
	virtual void Return() override;

private:
	// Private Functions
	void initialiseText();

	// Chosen Game Mode
	GameMode mode;

	// Score Manager 
	ScoreManager* scoreManager = nullptr;

	// Paddle Values
	Paddle* playerOne = nullptr;
	Paddle* playerTwo = nullptr;

	// AI Paddle Values
	AiPaddle* aiPaddle = nullptr;

	// Ball Values
	Ball* ball = nullptr;

	// Text Scores
	sf::Font font;
	sf::Text leftScoreText;
	sf::Text rightScoreText;
};

#endif // PLAYINGSTATE_H