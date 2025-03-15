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

void PlayingState::handleInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
	{
		StateManager::ChangeState(new MenuState());
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	{
		playerOne->moveUp();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
	{
		playerOne->moveDown();
	}
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