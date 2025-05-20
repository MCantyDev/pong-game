#ifndef BUTTONFACTORY_H
#define BUTTONFACTORY_H

#include "drawables/Button.h"
#include "GameEnums.h"

// Standard Library Includes
#include <memory>
#include <functional>

/**
 * @class ButtonFactory
 * @brief Factory class for creating buttons of different types in the Pong game.
 *
 * Implements the Factory Design Pattern to abstract the creation of Button objects.
 * Allows flexible creation of different button configurations based on type, label,
 * position, and click behavior.
 */
class ButtonFactory
{
public:
	/**
	 * @brief Creates a button of the specified type with provided properties.
	 *
	 * @param type The type of button to create (defined by ButtonType enum).
	 * @param text The label text displayed on the button.
	 * @param fontSize The font size of the button label.
	 * @param position The on-screen position of the button.
	 * @param onClick The callback function to be executed when the button is clicked.
	 * @return std::unique_ptr<Button> A unique pointer to the created Button object.
	 */
	static std::unique_ptr<Button> CreateButton(ButtonType type,
												const char *text,
												int fontSize,
												sf::Vector2f position,
												std::function<void()> onClick);
};

#endif // BUTTONFACTORY_H