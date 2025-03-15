#include "state/PlayingState.h"

// Different State Types
#include "state/MenuState.h"

PlayingState::PlayingState(StateManager* manager)
	: State(manager),
	playerOne(new Paddle(PaddleSide::LEFT)), playerTwo(new AiPaddle(PaddleSide::RIGHT)),
	ball(new Ball(playerOne, playerTwo))
{
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
		stateManager->changeState(new MenuState(stateManager));
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
}

void PlayingState::render()
{
	playerOne->draw();
	playerTwo->draw();
	
	ball->draw();
}