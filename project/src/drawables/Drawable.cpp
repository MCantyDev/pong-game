#include "drawables/Drawable.h"

Drawable::~Drawable()
{
	// Seems though the Shape is given to Drawable by a derived class, there is no need to "delete" shape
	shape = nullptr;
}

// Draw Function
void Drawable::draw(bool originVisable)
{
	RenderWindowManager::Draw(*shape);

	// Draw the Origin Point
	if (originVisable)
	{
		sf::CircleShape originMarker(3);
		originMarker.setFillColor(sf::Color::White);
		originMarker.setPosition({shape->getPosition().x, shape->getPosition().y});
		originMarker.setOrigin({3, 3});
		RenderWindowManager::Draw(originMarker);
	}
}

// Move Function
void Drawable::move(const sf::Vector2f &offset)
{
	shape->move(offset);
}
void Drawable::setPosition(const sf::Vector2f &position)
{
	shape->setPosition(position);
}

// Get Positional Data
sf::Vector2f Drawable::getCenter() const
{
	return shape->getPosition();
}
float Drawable::getCenterX() const
{
	return shape->getPosition().x;
}
float Drawable::getCenterY() const
{
	return shape->getPosition().y;
}

// Colour Functions
void Drawable::setColour(const sf::Color &colour)
{
	shape->setFillColor(colour);
}
void Drawable::setOutline(float thickness, const sf::Color &outlineColour)
{
	shape->setOutlineThickness(thickness);
	shape->setOutlineColor(outlineColour);
}