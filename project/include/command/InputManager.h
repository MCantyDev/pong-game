#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

// SFML Include
#include "SFML/Window.hpp"

#include "command/Commands.h"

#include "core/RenderWindowManager.h"

// Standard Library Include
#include <unordered_map>

class InputManager
{
public:
	~InputManager();
	static InputManager* GetInstance();

	static void HandleInput();

	static void SetBinding(sf::Keyboard::Key key, Command* command);
	static void InitialiseBindingsForState();
	static void ClearBindings();

private:
	InputManager() = default;
	static InputManager* instance;

	static std::unordered_map<sf::Keyboard::Key, Command*> keyBindings;

	// Copy Constructors
	InputManager(const InputManager&) = delete;
	InputManager& operator=(const InputManager&) = delete;
};

#endif // INPUTMANAGER_H