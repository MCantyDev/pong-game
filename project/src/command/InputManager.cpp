#include "command/InputManager.h"

InputManager* InputManager::instance = nullptr;
std::unordered_map<sf::Keyboard::Key, Command*> InputManager::keyBindings;

InputManager::~InputManager()
{
	for (auto& [key, command] : keyBindings)
	{
		delete command;
		command = nullptr;
	}

	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

InputManager* InputManager::GetInstance()
{
	if (!instance)
		instance = new InputManager();

	return instance;
}

void InputManager::HandleInput()
{
	if (RenderWindowManager::GetWindow()->hasFocus())
	{
		for (const auto& [key, command] : keyBindings)
		{
			if (sf::Keyboard::isKeyPressed(key) && command)
				command->execute();
		}
	}
}

void InputManager::SetBinding(sf::Keyboard::Key key, Command* command)
{
	keyBindings[key] = std::move(command);
}
void InputManager::InitialiseBindingsForState()
{
	// Initialise Some values
	keyBindings[sf::Keyboard::Key::W] = new PlayerOneMoveUp(StateManager::GetState());
	keyBindings[sf::Keyboard::Key::S] = new PlayerOneMoveDown(StateManager::GetState());

	keyBindings[sf::Keyboard::Key::Up] = new PlayerTwoMoveUp(StateManager::GetState());
	keyBindings[sf::Keyboard::Key::Down] = new PlayerTwoMoveDown(StateManager::GetState());

	keyBindings[sf::Keyboard::Key::Enter] = new Return(StateManager::GetState());
	keyBindings[sf::Keyboard::Key::Escape] = new Pause(StateManager::GetState());
}
void InputManager::ClearBindings()
{
	keyBindings.clear();
}