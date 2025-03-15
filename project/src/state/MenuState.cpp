#include "state/MenuState.h"

// Different States
#include "state/PlayingState.h"

MenuState::MenuState(StateManager* manager)
	: State(manager), window(*RenderWindowManager::GetWindow())
{
	arial.openFromFile("fonts/Arial.ttf");

	initialiseText();
}

void MenuState::handleInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
	{
		stateManager->changeState(new PlayingState(stateManager));
	}
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
