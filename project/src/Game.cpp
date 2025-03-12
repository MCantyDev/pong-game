#include "Game.h"

Game::Game()
	: 
	window(sf::VideoMode({ (unsigned int)WIDTH, (unsigned int)HEIGHT }), title, { sf::Style::Titlebar | sf::Style::Close }),
	stateManager(StateManager(window)), deltaClock(DeltaTimeClock::GetInstance())
{
	window.setVerticalSyncEnabled(true);

	initialiseMusic();
	backgroundMusic.play();
}

void Game::run()
{
	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
				break;
			}
		}

		window.clear(sf::Color(50, 50, 50));
		
		deltaClock->update();

		stateManager.handleInput();
		stateManager.update();
		stateManager.render();

		window.display();
	}
}

void Game::initialiseMusic()
{
	if (backgroundMusic.openFromFile("sounds/background_music.mp3"))

	// Music Setting
	backgroundMusic.setVolume(15);
	backgroundMusic.setLooping(true);
}
