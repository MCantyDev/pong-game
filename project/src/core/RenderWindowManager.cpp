#include "core/RenderWindowManager.h"

sf::RenderWindow *RenderWindowManager::instance = nullptr;

RenderWindowManager::~RenderWindowManager()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

sf::RenderWindow *RenderWindowManager::GetInstance()
{
	if (!instance)
	{
		instance = new sf::RenderWindow(sf::VideoMode({1200, 800}), "Pong Game", {sf::Style::Titlebar | sf::Style::Close});
	}
	return instance;
}

void RenderWindowManager::DeleteInstance()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

void RenderWindowManager::Draw(const sf::Drawable &drawable, const sf::RenderStates &states)
{
	if (!instance)
	{
		std::cerr << "Error: Please Instantiate a Render Window first" << std::endl;
		return;
	}
	instance->draw(drawable, states);
}
void RenderWindowManager::Draw(const sf::Vertex *vertices,
							   std::size_t vertexCount,
							   sf::PrimitiveType type,
							   const sf::RenderStates &states)
{
	if (!instance)
	{
		std::cerr << "Error: Please Instantiate a Render Window first" << std::endl;
		return;
	}
	instance->draw(vertices, vertexCount, type, states);
}
void RenderWindowManager::Draw(const sf::VertexBuffer &vertexBuffer, const sf::RenderStates &states)
{
	if (!instance)
	{
		std::cerr << "Error: Please Instantiate a Render Window first" << std::endl;
		return;
	}
	instance->draw(vertexBuffer, states);
}
void RenderWindowManager::Draw(const sf::VertexBuffer &vertexBuffer,
							   std::size_t firstVertex,
							   std::size_t vertexCount,
							   const sf::RenderStates &states)
{
	if (!instance)
	{
		std::cerr << "Error: Please Instantiate a Render Window first" << std::endl;
		return;
	}
	instance->draw(vertexBuffer, firstVertex, vertexCount, states);
}
void RenderWindowManager::CloseWindow()
{
	if (!instance)
	{
		std::cerr << "Error: Please Instantiate a Render Window first" << std::endl;
		return;
	}
	instance->close();
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
