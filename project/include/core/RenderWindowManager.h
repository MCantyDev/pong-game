#ifndef RENDERWINDOWMANAGER_H
#define RENDERWINDOWMANAGER_H

// SFML Include
#include "SFML/Graphics.hpp"

// Standard Library Include
#include <iostream>

/**
 * @class RenderWindowManager
 * @brief Singleton class that manages the main SFML render window for the Pong game.
 *
 * Provides global access to the render window and convenient overloaded draw methods
 * for rendering various drawable objects and vertex data.
 */
class RenderWindowManager
{
public:
	/**
	 * @brief Destructor to clean up the render window.
	 */
	~RenderWindowManager();

	/**
	 * @brief Retrieves the singleton instance of the SFML RenderWindow.
	 * @return Pointer to the sf::RenderWindow.
	 */
	static sf::RenderWindow *GetInstance();

	/**
	 * @brief Deletes the singleton instance, freeing allocated resources.
	 */
	static void DeleteInstance();

	/**
	 * @brief Gets the current width of the render window.
	 * @return Width in pixels as a float.
	 */
	static float GetWidth();

	/**
	 * @brief Gets the current height of the render window.
	 * @return Height in pixels as a float.
	 */
	static float GetHeight();

	/**
	 * @brief Draws a single SFML drawable object to the render window.
	 *
	 * Common drawable types include shapes, sprites, text, and other sf::Drawable derivatives.
	 *
	 * @param drawable The drawable object to render.
	 * @param states Optional render states (transformations, shaders, blend modes, etc.). Defaults to sf::RenderStates::Default.
	 */
	static void Draw(const sf::Drawable &drawable, const sf::RenderStates &states = sf::RenderStates::Default);

	/**
	 * @brief Draws an array of vertices as a specified primitive type to the render window.
	 *
	 * Useful for custom vertex data rendering such as points, lines, triangles, etc.
	 *
	 * @param vertices Pointer to the first vertex in the array.
	 * @param vertexCount Number of vertices to draw.
	 * @param type The primitive type to draw (e.g., sf::Points, sf::Lines, sf::Triangles).
	 * @param states Optional render states to apply during drawing. Defaults to sf::RenderStates::Default.
	 */
	static void Draw(const sf::Vertex *vertices,
					 std::size_t vertexCount,
					 sf::PrimitiveType type,
					 const sf::RenderStates &states = sf::RenderStates::Default);

	/**
	 * @brief Draws an entire vertex buffer to the render window.
	 *
	 * Vertex buffers optimize rendering of static or dynamic vertex arrays.
	 *
	 * @param vertexBuffer The vertex buffer to draw.
	 * @param states Optional render states to apply. Defaults to sf::RenderStates::Default.
	 */
	static void Draw(const sf::VertexBuffer &vertexBuffer, const sf::RenderStates &states = sf::RenderStates::Default);

	/**
	 * @brief Draws a subset of a vertex buffer to the render window.
	 *
	 * Allows rendering a specified range of vertices within a vertex buffer.
	 *
	 * @param vertexBuffer The vertex buffer containing the vertices.
	 * @param firstVertex Index of the first vertex to draw.
	 * @param vertexCount Number of vertices to draw starting from firstVertex.
	 * @param states Optional render states to apply. Defaults to sf::RenderStates::Default.
	 */
	static void Draw(const sf::VertexBuffer &vertexBuffer,
					 std::size_t firstVertex,
					 std::size_t vertexCount,
					 const sf::RenderStates &states = sf::RenderStates::Default);

	/**
	 * @brief Closes the render window.
	 */
	static void CloseWindow();

private:
	RenderWindowManager() = default;

	static sf::RenderWindow *instance;

	// Deleted copy constructors to prevent copying the singleton.
	RenderWindowManager(const RenderWindowManager &) = delete;
	RenderWindowManager &operator=(const RenderWindowManager &) = delete;
};

#endif // RENDERWINDOWMANAGER_H