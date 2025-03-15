#include "state/MenuState.h"

// Different States
#include "state/PlayingState.h"

MenuState::MenuState()
	: window(*RenderWindowManager::GetWindow())
{
	if (arial.openFromFile("fonts/Arial.ttf"))
		initialiseText();
	else
		throw std::runtime_error("Failed to Load Font");
}

void MenuState::update()
{

}

void MenuState::render()
{
	window.draw(titleText);
	window.draw(instructionText);
}

void MenuState::initialiseText()
{
	sf::FloatRect ttb = titleText.getLocalBounds();
	sf::FloatRect it = instructionText.getLocalBounds();

	titleText.setOrigin({ ttb.size.x / 2, ttb.size.y / 2 });
	titleText.setPosition({ (float)window.getSize().x / 2, 50.f });

	instructionText.setOrigin({ it.size.x / 2, it.size.y / 2 });
	instructionText.setPosition({ (float)window.getSize().x / 2, (float)window.getSize().y / 2 });
}

// Commands
void MenuState::PlayerOneMoveUp()
{
	return;
}
void MenuState::PlayerOneMoveDown()
{
	return;
}

void MenuState::PlayerTwoMoveUp()
{
	return;
}
void MenuState::PlayerTwoMoveDown()
{
	return;
}

void MenuState::Pause()
{
	return;
}
void MenuState::Select()
{
	return;
}
void MenuState::Return()
{
	StateManager::ChangeState(new PlayingState());
}