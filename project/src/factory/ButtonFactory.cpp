#include "factory/ButtonFactory.h"

// Button Types
#include "utility/RectButton.h"

std::unique_ptr<Button> ButtonFactory::CreateButton(ButtonType type,
	const char* text, int fontSize,
	sf::Vector2f position,
	std::function<void()> onClick)
{
	if (type == ButtonType::RECTANGLE_BUTTON)
	{
		return std::make_unique<RectButton>(text, fontSize, position, onClick);
	}

	return nullptr;
}