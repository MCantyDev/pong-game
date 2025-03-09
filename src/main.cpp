#define SFML_STATIC

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Pong");

	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>() ||
				event->is<sf::Event::KeyPressed>() && event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape)
			{
				window.close();
				break;
			}

			window.clear(sf::Color(50, 50, 50));
			window.display();
		}
	}
}