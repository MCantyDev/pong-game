#include "Game.h"

Game::Game()
	: window(RenderWindowManager::GetInstance()), stateManager(StateManager::GetInstance()),
	  deltaClock(DeltaTimeClock::GetInstance()), soundManager(SoundManager::GetInstance())
{
	window->setVerticalSyncEnabled(true);

	initialiseSounds();
	initialiseBackgroundMusic();
	SoundManager::Play("background", Sound::MUSIC);
}

void Game::run()
{
	while (window->isOpen())
	{
		while (const std::optional event = window->pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window->close();
				break;
			}
		}

		window->clear(sf::Color(25, 25, 25));

		deltaClock->update();

		StateManager::CheckStateChange();
		InputManager::HandleInput();

		stateManager->update();
		stateManager->render();

		window->display();
	}
}

void Game::initialiseSounds()
{
	soundManager->AddSound("paddle_bounce", "sounds/paddle_bounce.wav");
	soundManager->getSound("paddle_bounce")->setVolume(10);

	soundManager->AddSound("wall_bounce", "sounds/wall_bounce.wav");
	soundManager->getSound("wall_bounce")->setVolume(10);

	soundManager->AddSound("score_point", "sounds/score_point.wav");
	soundManager->getSound("score_point")->setVolume(10);
}

void Game::initialiseBackgroundMusic()
{
	soundManager->AddMusic("background", "sounds/background_music.mp3");

	auto backgroundMusic = soundManager->getMusic("background");

	if (backgroundMusic)
	{
		backgroundMusic->setVolume(15);
		backgroundMusic->setLooping(true);
	}
}
