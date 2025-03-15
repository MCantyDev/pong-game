#include "Game.h"

Game::Game()
	: 
	window(*RenderWindowManager::GetWindow()), 
	deltaClock(DeltaTimeClock::GetInstance()), soundManager(SoundManager::GetInstance())
{
	window.setVerticalSyncEnabled(true);

	initialiseSounds();
	initialiseBackgroundMusic();
	soundManager->GetMusic("background")->play();
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

void Game::initialiseSounds()
{
	soundManager->addSound("paddle_bounce", "sounds/paddle_bounce.wav");
	soundManager->addSound("wall_bounce", "sounds/wall_bounce.wav");
	soundManager->addSound("score_point", "sounds/score_point.wav");
}

void Game::initialiseBackgroundMusic()
{
	soundManager->addMusic("background", "sounds/background_music.mp3");

	auto backgroundMusic = soundManager->GetMusic("background");

	if (backgroundMusic)
	{
		backgroundMusic->setVolume(15);
		backgroundMusic->setLooping(true);
	}
}
