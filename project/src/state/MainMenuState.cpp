#include "state/MainMenuState.h"

// Different States
#include "state/PlayingState.h"

MainMenuState::MainMenuState()
{
	if (!font.openFromFile("fonts/MainFont.ttf"))
		throw std::runtime_error("Failed to Load Font");

	initialiseText();
	initialiseGraphics();
	initialiseButtons();
}

void MainMenuState::update()
{
	try
	{
		for (auto &button : buttons)
		{
			button->checkHovered();
			button->checkClicked();
		}
	}
	catch (std::runtime_error e)
	{
		std::cerr << "Exception Caught - Error: " << e.what() << std::endl;
	}
}

void MainMenuState::render()
{
	// Draw Graphics
	RenderWindowManager::Draw(ball);

	RenderWindowManager::Draw(leftPaddle);
	RenderWindowManager::Draw(rightPaddle);

	RenderWindowManager::Draw(titleText);

	for (auto &button : buttons)
	{
		button->draw();
	}
}

void MainMenuState::initialiseText()
{
	sf::FloatRect ttb = titleText.getLocalBounds();

	titleText.setOrigin({ttb.size.x / 2, ttb.size.y / 2});
	titleText.setPosition({RenderWindowManager::GetWidth() / 2, (RenderWindowManager::GetHeight() / 2) - 50.f});
}

void MainMenuState::initialiseGraphics()
{
	// Left Paddle
	leftPaddle.setSize(sf::Vector2f(40, 120) - sf::Vector2f(4, 4));
	leftPaddle.setFillColor(sf::Color(200, 50, 50));
	leftPaddle.setOutlineThickness(4);
	leftPaddle.setOutlineColor(sf::Color::Black);
	leftPaddle.setOrigin({20, 60});
	leftPaddle.setPosition({30.f, (RenderWindowManager::GetHeight() / 2) + 200.f});

	// Right Paddle
	rightPaddle.setSize(sf::Vector2f(40, 120) - sf::Vector2f(4, 4));
	rightPaddle.setFillColor(sf::Color(50, 50, 200));
	rightPaddle.setOutlineThickness(4);
	rightPaddle.setOutlineColor(sf::Color::Black);
	rightPaddle.setOrigin({20, 60});
	rightPaddle.setPosition({RenderWindowManager::GetWidth() - 30.f, (RenderWindowManager::GetHeight() / 2) - 200.f});

	// Ball
	ball.setRadius(15.f - 4);
	ball.setOutlineThickness(4);
	ball.setOutlineColor(sf::Color::Black);
	ball.setOrigin({7.5, 7.5});
	ball.setPosition({RenderWindowManager::GetWidth() - 200.f, 250.f});
}

void MainMenuState::initialiseButtons()
{
	buttons.push_back(ButtonFactory::CreateButton(ButtonType::RECTANGLE_BUTTON,
												  "Play (vs Ai)", 30,
												  sf::Vector2f(RenderWindowManager::GetWidth() / 2, RenderWindowManager::GetHeight() / 2 + 50.f),
												  [this]()
												  { this->playerVsAi(); }));

	buttons.push_back(ButtonFactory::CreateButton(ButtonType::RECTANGLE_BUTTON,
												  "Play (2 player Local)", 30,
												  sf::Vector2f(RenderWindowManager::GetWidth() / 2, RenderWindowManager::GetHeight() / 2 + 125.f),
												  [this]()
												  { this->playerVsPlayer(); }));

	buttons.push_back(ButtonFactory::CreateButton(ButtonType::RECTANGLE_BUTTON,
												  "Exit", 30,
												  sf::Vector2f(RenderWindowManager::GetWidth() / 2, RenderWindowManager::GetHeight() / 2 + 200.f),
												  [this]()
												  { this->closeWindow(); }));
}

// Button On Click functions
void MainMenuState::playerVsAi()
{
	StateManager::SetChangeState(std::make_unique<PlayingState>(GameMode::PLAYER_VS_COMPUTER));
}
void MainMenuState::playerVsPlayer()
{
	StateManager::SetChangeState(std::make_unique<PlayingState>(GameMode::LOCAL_PLAYER_VS_PLAYER));
}
void MainMenuState::closeWindow()
{
	RenderWindowManager::CloseWindow();
}

// Commands
void MainMenuState::PlayerOneMoveUp()
{
	return;
}
void MainMenuState::PlayerOneMoveDown()
{
	return;
}

void MainMenuState::PlayerTwoMoveUp()
{
	return;
}
void MainMenuState::PlayerTwoMoveDown()
{
	return;
}

void MainMenuState::Pause()
{
	return;
}
void MainMenuState::Select()
{
	return;
}
void MainMenuState::Return()
{
	return;
}