#include "factory/ButtonFactory.h"

// Button Types
#include "drawables/RectButton.h"

std::unique_ptr<Button> ButtonFactory::CreateButton(ButtonType type,
	const char* text, int fontSize,
	sf::Vector2f position,
	std::function<void()> onClick)
{
	// Update to Switch statement as looks cleaner
	switch (type) {
		case ButtonType::RECTANGLE_BUTTON:
			return std::make_unique<RectButton>(text, fontSize, position, onClick);

		default:
			return nullptr;
	}
}