#ifndef RENDERWINDOWMANAGER_H
#define RENDERWINDOWMANAGER_H

// SFML Include
#include "SFML/Graphics.hpp"

// Standard Library Include
#include <iostream>

class RenderWindowManager
{
public:
	~RenderWindowManager();

	static sf::RenderWindow* GetWindow();
	static float GetWidth();
	static float GetHeight();

private:
	RenderWindowManager() = default;
	static sf::RenderWindow* instance;

	RenderWindowManager(const RenderWindowManager&) = delete;
	RenderWindowManager& operator=(const RenderWindowManager&) = delete;
};

#endif // RENDERWINDOWMANAGER_H