#include "command/InputManager.h"

InputManager *InputManager::instance = nullptr;
std::unordered_map<sf::Keyboard::Key, Command *> InputManager::keyBindings;

InputManager::~InputManager()
{
	for (auto &[key, command] : keyBindings)
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

InputManager *InputManager::GetInstance()
{
	if (!instance)
		instance = new InputManager();

	return instance;
}

void InputManager::DeleteInstance()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

void InputManager::HandleInput()
{
	if (RenderWindowManager::GetInstance()->hasFocus())
	{
		for (const auto &[key, command] : keyBindings)
		{
			if (sf::Keyboard::isKeyPressed(key) && command)
				command->execute();
		}
	}
}

void InputManager::SetBinding(sf::Keyboard::Key key, Command *command)
{
	keyBindings[key] = std::move(command);
}

// Could be done differently but there was no need to swap within codebase (As not many commands required for application)
// One way would be using a JSON object with all Input settings and binding the appropriate Keys to the correct values defaulting to null for any values that just dont exist in the codebase
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