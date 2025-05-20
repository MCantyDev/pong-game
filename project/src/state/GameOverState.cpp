#include "state/GameOverState.h"

// State Includes
#include "state/MainMenuState.h"
#include "state/PlayingState.h"

GameOverState::GameOverState(PaddleSide winner, GameMode mode)
	: winner(winner), mode(mode)
{
	// Load Font
	if (!font.openFromFile("fonts/MainFont.ttf"))
		throw std::runtime_error("Font Not Loaded");

	initialiseText(winner, mode);
	initialiseButtons();
}

void GameOverState::update()
{
	for (auto &button : buttons)
	{
		button->checkHovered();
		button->checkClicked();
	}
}

void GameOverState::render()
{
	for (auto &button : buttons)
	{
		button->draw();
	}
	RenderWindowManager::Draw(scoreText);
	RenderWindowManager::Draw(winnerText);
}

void GameOverState::initialiseText(PaddleSide winner, GameMode mode)
{
	scoreText.setString(
		std::to_string(ScoreManager::GetScore(PaddleSide::LEFT)) + " - " + std::to_string(ScoreManager::GetScore(PaddleSide::RIGHT)));

	if (mode == GameMode::PLAYER_VS_COMPUTER)
	{
		if (winner == PaddleSide::LEFT)
			winnerText.setString("You Win!");
		else
			winnerText.setString("You Lose!");
	}
	else
	{
		if (winner == PaddleSide::LEFT)
			winnerText.setString("Player One Wins!");
		else
			winnerText.setString("Player Two Wins!");
	}

	// Score Text
	sf::FloatRect stb = scoreText.getLocalBounds();
	scoreText.setOrigin({stb.size.x / 2, stb.size.y / 2});
	scoreText.setPosition({(RenderWindowManager::GetWidth() / 2), (RenderWindowManager::GetHeight() / 2) - 100.f});

	// Winner Text
	sf::FloatRect wtb = winnerText.getLocalBounds();
	winnerText.setOrigin({wtb.size.x / 2, wtb.size.y / 2});
	winnerText.setPosition({(RenderWindowManager::GetWidth() / 2), (RenderWindowManager::GetHeight() / 2) + 25.f});
}

void GameOverState::initialiseButtons()
{
	buttons.push_back(ButtonFactory::CreateButton(
		ButtonType::RECTANGLE_BUTTON, "Play Again", 30,
		sf::Vector2f({(RenderWindowManager::GetWidth() / 2) - 200.f, (RenderWindowManager::GetHeight() / 2) + 175.f}),
		[this]()
		{ playAgain(); }));

	buttons.push_back(ButtonFactory::CreateButton(
		ButtonType::RECTANGLE_BUTTON, "Main Menu", 30,
		sf::Vector2f((RenderWindowManager::GetWidth() / 2) + 200.f, (RenderWindowManager::GetHeight() / 2) + 175.f),
		[this]()
		{ mainMenu(); }));

	buttons.push_back(ButtonFactory::CreateButton(ButtonType::RECTANGLE_BUTTON,
												  "Exit", 30,
												  sf::Vector2f(RenderWindowManager::GetWidth() / 2, RenderWindowManager::GetHeight() / 2 + 250.f),
												  [this]()
												  { this->closeWindow(); }));
}

// Button Functions
void GameOverState::playAgain()
{
	StateManager::SetChangeState(std::make_unique<PlayingState>(mode));
}
void GameOverState::mainMenu()
{
	StateManager::SetChangeState(std::make_unique<MainMenuState>());
}
void GameOverState::closeWindow()
{
	RenderWindowManager::CloseWindow();
}

// Command Overrides
void GameOverState::PlayerOneMoveUp()
{
	return;
}
void GameOverState::PlayerOneMoveDown()
{
	return;
}
void GameOverState::PlayerTwoMoveUp()
{
	return;
}
void GameOverState::PlayerTwoMoveDown()
{
	return;
}
void GameOverState::Pause()
{
	return;
}
void GameOverState::Select()
{
	return;
}
void GameOverState::Return()
{
	return;
}