#include "state/PlayingState.h"

// Different State Types
#include "state/MainMenuState.h"

PlayingState::PlayingState()
	:
	scoreManager(ScoreManager::GetInstance()),
	playerOne(new Paddle(PaddleSide::LEFT)), playerTwo(new AiPaddle(PaddleSide::RIGHT)),
	ball(new Ball(playerOne, playerTwo)),
	leftScoreText(font, "0", 50.f),
	rightScoreText(font, "0", 50.f)
{
	ScoreManager::ResetScores();

	playerOne->setColour(sf::Color(200, 50, 50));
	playerTwo->setColour(sf::Color(50, 50, 200));
	
	if (true) // Will be changed to If Mode is Player VS AI
	{
		aiPaddle = static_cast<AiPaddle*>(playerTwo);
		aiPaddle->setObject(ball);
	}

	if (!font.openFromFile("fonts/MainFont.ttf"))
		throw std::runtime_error("Failed to load font - fonts/MainFont.tff");

	initialiseText();
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
		StateManager::ChangeState(new MainMenuState());
	}

	leftScoreText.setString(std::to_string(ScoreManager::GetScore(PaddleSide::LEFT)));
	rightScoreText.setString(std::to_string(ScoreManager::GetScore(PaddleSide::RIGHT)));
}

void PlayingState::render()
{
	RenderWindowManager::GetWindow()->draw(leftScoreText);
	RenderWindowManager::GetWindow()->draw(rightScoreText);

	playerOne->draw();
	playerTwo->draw();
	
	ball->draw();
}

void PlayingState::initialiseText()
{
	// Left Score Text
	sf::FloatRect lstr = leftScoreText.getLocalBounds();
	leftScoreText.setOrigin({ lstr.size.x / 2, lstr.size.y / 2 });
	leftScoreText.setPosition({ (RenderWindowManager::GetWidth() / 2) - 100.f, 75.f });

	// Right Score Text
	sf::FloatRect rstr = rightScoreText.getLocalBounds();
	rightScoreText.setOrigin({ rstr.size.x / 2, rstr.size.y / 2 });
	rightScoreText.setPosition({ (RenderWindowManager::GetWidth() / 2) + 100.f, 75.f });
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
	StateManager::ChangeState(new MainMenuState());
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