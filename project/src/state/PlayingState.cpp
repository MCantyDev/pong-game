#include "state/PlayingState.h"

// Different State Types
#include "state/MenuState.h"

PlayingState::PlayingState()
	:
	scoreManager(ScoreManager::GetInstance()),
	playerOne(new Paddle(PaddleSide::LEFT)), playerTwo(new AiPaddle(PaddleSide::RIGHT)),
	ball(new Ball(playerOne, playerTwo))
{
	ScoreManager::ResetScores();

	playerOne->setColour(sf::Color(200, 50, 50));

	playerTwo->setColour(sf::Color(50, 50, 200));
	
	if (true) // Will be changed to If Mode is Player VS AI
	{
		aiPaddle = static_cast<AiPaddle*>(playerTwo);
		aiPaddle->setObject(ball);
	}
}

PlayingState::~PlayingState()
{
	delete playerOne;
	playerOne = nullptr;

	delete playerTwo;
	playerTwo = nullptr;
}

void PlayingState::update()
{
	ball->update();

	if (aiPaddle)
		aiPaddle->update();

	if (scoreManager->checkGameEnd())
	{
		StateManager::ChangeState(new MenuState());
	}
}

void PlayingState::render()
{
	playerOne->draw();
	playerTwo->draw();
	
	ball->draw();
}


// Commands
void PlayingState::PlayerOneMoveUp()
{
	playerOne->moveUp();
}
void PlayingState::PlayerOneMoveDown()
{
	playerOne->moveDown();
}

void PlayingState::PlayerTwoMoveUp()
{
	if (true) // Will be changed to Game Mode check
		return;
	playerTwo->moveUp();
}
void PlayingState::PlayerTwoMoveDown()
{
	if (true) // Will be changed to Game Mode check
		return;

	playerTwo->moveDown();
}

void PlayingState::Pause()
{
	// Go to Pause state
	StateManager::ChangeState(new MenuState());
}
void PlayingState::Select()
{
	// Select -> Does nothing in Playing State
	return;
}
void PlayingState::Return()
{
	// Return (Go back to previous state) -> Does nothing in Playing State
	return;
}