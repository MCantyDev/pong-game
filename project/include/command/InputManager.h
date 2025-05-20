#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

// SFML Include
#include "SFML/Window.hpp"

#include "command/Commands.h"

#include "core/RenderWindowManager.h"

// Standard Library Include
#include <unordered_map>

/**
 * @class InputManager
 * @brief Manages the mapping of keyboard inputs to commands within the Pong game.
 *
 * Implements the Singleton pattern to ensure only one InputManager instance exists.
 * Utilises the Command pattern by binding keyboard keys to Command objects that encapsulate input actions.
 */
class InputManager
{
public:
	/**
	 * @brief Destructor to clean up resources.
	 */
	~InputManager();

	/**
	 * @brief Returns the singleton instance of the InputManager.
	 * @return Pointer to the single InputManager instance.
	 */
	static InputManager *GetInstance();

	/**
	 * @brief Deletes the singleton instance, freeing allocated resources.
	 */
	static void DeleteInstance();

	/**
	 * @brief Processes user input by checking for key press events and executing the bound commands.
	 */
	static void HandleInput();

	/**
	 * @brief Updates or adds a key-command binding.
	 *
	 * Intended for dynamic rebinding (e.g., via a settings menu, not currently implemented).
	 * @param key The keyboard key to bind.
	 * @param command Pointer to the Command to execute when the key is pressed.
	 */
	static void SetBinding(sf::Keyboard::Key key, Command *command);

	/**
	 * @brief Initializes key bindings for the current game state.
	 *
	 * Sets up default mappings between keys and commands relevant to the active state.
	 */
	static void InitialiseBindingsForState();

	/**
	 * @brief Clears all current key-command bindings.
	 */
	static void ClearBindings();

private:
	InputManager() = default;

	static InputManager *instance;

	static std::unordered_map<sf::Keyboard::Key, Command *> keyBindings;

	// Deleted copy constructors to prevent copying of the singleton.
	InputManager(const InputManager &) = delete;
	InputManager &operator=(const InputManager &) = delete;
};

#endif // INPUTMANAGER_H