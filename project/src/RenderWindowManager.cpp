#include "RenderWindowManager.h"

sf::RenderWindow* RenderWindowManager::instance = nullptr;

RenderWindowManager::~RenderWindowManager()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

sf::RenderWindow* RenderWindowManager::GetWindow()
{
	if (!instance)
	{
		instance = new sf::RenderWindow(sf::VideoMode({ 1200, 800 }), "Pong Game", { sf::Style::Titlebar | sf::Style::Close });
	}
	return instance;
}

float RenderWindowManager::GetHeight()
{
	if (!instance)
	{
		std::cerr << "Error: Please Instantiate a Render Window first" << std::endl;
		return 0.f;
	}
	return instance->getSize().y;
}

float RenderWindowManager::GetWidth()
{
	if (!instance)
	{
		std::cerr << "Error: Please Instantiate a Render Window first" << std::endl;
		return 0.f;
	}
	return instance->getSize().x;
}
