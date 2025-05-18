#ifndef BUTTONFACTORY_H
#define BUTTONFACTORY_H

#include "drawables/Button.h"

// Standard Library Includes
#include <memory>
#include <functional>

enum class ButtonType
{
	RECTANGLE_BUTTON
};

class ButtonFactory
{
public:
	static std::unique_ptr<Button> CreateButton(ButtonType type,
		const char* text, int fontSize, 
		sf::Vector2f position,
		std::function<void()> onClick);
};

#endif // BUTTONFACTORY_H