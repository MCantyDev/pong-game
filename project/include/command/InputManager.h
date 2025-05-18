#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

// SFML Include
#include "SFML/Window.hpp"

#include "command/Commands.h"

#include "core/RenderWindowManager.h"

// Standard Library Include
#include <unordered_map>

/*
* @class Input Manager
* @brief Input Manager binds commands to keyboard inputs within the Pong game
* 
* InputManager follows the singleton pattern as only one InputManager should be present throughout the whole application
* Binding Commands to Input to follow the Command Pattern
* 
*/
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