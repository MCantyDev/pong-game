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

	// Overloading the Most Common Draw Functions in SFML
	// These functions allow rendering various types of drawable objects, such as shapes, sprites, vertex arrays, and vertex buffers, 
	// with optional transformations, shaders, and other render states.

	// 1. Draw a single sf::Drawable object (e.g., shapes, sprites, text, etc.)
	// 2. Draw a custom set of vertices as a specific primitive type (e.g., points, lines, triangles, etc.)
	// 3. Draw an entire sf::VertexBuffer (batch of vertices for efficient drawing)
	// 4. Draw a subset of a sf::VertexBuffer (specify range of vertices to draw)
	// 5. Draw an entire sf::VertexBuffer (same as 3 but no extra parameters)

    static void Draw(const sf::Drawable& drawable, const sf::RenderStates& states = sf::RenderStates::Default);
    static void Draw(const sf::Vertex* vertices,
        std::size_t         vertexCount,
        sf::PrimitiveType       type,
        const sf::RenderStates& states = sf::RenderStates::Default);
    static void Draw(const sf::VertexBuffer& vertexBuffer, const sf::RenderStates& states = sf::RenderStates::Default);
    static void Draw(const sf::VertexBuffer& vertexBuffer,
        std::size_t         firstVertex,
        std::size_t         vertexCount,
        const sf::RenderStates& states = sf::RenderStates::Default);
	static void CloseWindow();

private:
	RenderWindowManager() = default;
	static sf::RenderWindow* instance;

	RenderWindowManager(const RenderWindowManager&) = delete;
	RenderWindowManager& operator=(const RenderWindowManager&) = delete;
};

#endif // RENDERWINDOWMANAGER_H