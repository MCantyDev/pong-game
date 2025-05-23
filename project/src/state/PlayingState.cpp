#include "state/PlayingState.h"

// Different State Types
#include "state/MainMenuState.h"
#include "state/GameOverState.h"

PlayingState::PlayingState(GameMode mode)
	: scoreManager(ScoreManager::GetInstance()), mode(mode),
	  playerOne(new Paddle(PaddleSide::LEFT)),
	  playerTwo((mode == GameMode::PLAYER_VS_COMPUTER) ? new AiPaddle(PaddleSide::RIGHT) : new Paddle(PaddleSide::RIGHT)),
	  ball(new Ball(playerOne, playerTwo)),
	  leftScoreText(font, "0", 50.f),
	  rightScoreText(font, "0", 50.f)
{
	ScoreManager::ResetScores();

	playerOne->setColour(sf::Color(200, 50, 50));
	playerTwo->setColour(sf::Color(50, 50, 200));

	if (mode == GameMode::PLAYER_VS_COMPUTER) // Will be changed to If Mode is Player VS AI
	{
		aiPaddle = static_cast<AiPaddle *>(playerTwo);
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
		StateManager::SetChangeState(
			std::make_unique<GameOverState>(ScoreManager::GetWinner(), mode));

	leftScoreText.setString(std::to_string(ScoreManager::GetScore(PaddleSide::LEFT)));
	rightScoreText.setString(std::to_string(ScoreManager::GetScore(PaddleSide::RIGHT)));
}

void PlayingState::render()
{
	RenderWindowManager::Draw(leftScoreText);
	RenderWindowManager::Draw(rightScoreText);

	ball->draw(); // Must be drawn before paddles to make it not overlap

	playerOne->draw();
	playerTwo->draw();
}

void PlayingState::initialiseText()
{
	// Left Score Text
	sf::FloatRect lstr = leftScoreText.getLocalBounds();
	leftScoreText.setOrigin({lstr.size.x / 2, lstr.size.y / 2});
	leftScoreText.setPosition({(RenderWindowManager::GetWidth() / 2) - 100.f, 75.f});

	// Right Score Text
	sf::FloatRect rstr = rightScoreText.getLocalBounds();
	rightScoreText.setOrigin({rstr.size.x / 2, rstr.size.y / 2});
	rightScoreText.setPosition({(RenderWindowManager::GetWidth() / 2) + 100.f, 75.f});
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
	if (mode == GameMode::PLAYER_VS_COMPUTER)
		return;

	playerTwo->moveUp();
}
void PlayingState::PlayerTwoMoveDown()
{
	if (mode == GameMode::PLAYER_VS_COMPUTER)
		return;

	playerTwo->moveDown();
}

void PlayingState::Pause()
{
	// Go to Pause state
	StateManager::SetChangeState(std::make_unique<MainMenuState>());
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