#include "core/SoundManager.h"

// Static Values
SoundManager *SoundManager::instance = nullptr;

std::unordered_map<std::string, sf::SoundBuffer> SoundManager::soundBufferMap;
std::unordered_map<std::string, sf::Sound *> SoundManager::soundMap;
std::unordered_map<std::string, sf::Music *> SoundManager::musicMap;

SoundManager::~SoundManager()
{
	// Delete all Sound Resources (as Raw Pointers used)
	for (auto &sound : soundMap)
	{
		delete sound.second;
		sound.second = nullptr;
	}

	// Delete all Music Resources (as Raw Pointers used)
	for (auto &music : musicMap)
	{
		delete music.second;
		music.second = nullptr;
	}

	// Then Clean up the Instance Pointer
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

SoundManager *SoundManager::GetInstance()
{
	if (!instance)
		instance = new SoundManager();

	return instance;
}

void SoundManager::DeleteInstance()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

void SoundManager::Play(std::string name, Sound type)
{
	switch (type)
	{
		case Sound::EFFECT:
		{
			sf::Sound* effect = getSound(name);
			effect->play();
			break;
		}

		case Sound::MUSIC:
		{
			sf::Music* music = getMusic(name);
			music->play();
			break;
		}

		default:
		{
			throw std::runtime_error("Type not recognised");
		}
	}
}

void SoundManager::Pause(std::string name, Sound type)
{
	switch (type)
	{
		case Sound::EFFECT:
		{
			sf::Sound* effect = getSound(name);
			effect->pause();
			break;
		}

		case Sound::MUSIC:
		{
			sf::Music* music = getMusic(name);
			music->pause();
			break;
		}

		default:
			throw std::runtime_error("Type not recognised");
	}
}

sf::Sound* SoundManager::getSound(std::string soundName)
{
	auto it = soundMap.find(soundName);
	if (it != soundMap.end())
	{
		return it->second;
	}

	throw std::runtime_error("Sound not found: " + soundName);
}

sf::Music* SoundManager::getMusic(std::string musicName)
{
	auto it = musicMap.find(musicName);
	if (it != musicMap.end())
	{
		return it->second;
	}

	throw std::runtime_error("Music not found: " + musicName);
}

void SoundManager::AddSound(std::string soundName, std::string filePath)
{
	sf::SoundBuffer buffer;
	if (!buffer.loadFromFile(filePath))
	{
		throw std::runtime_error("Failed to Load Filepath: " + filePath);
	}
	soundBufferMap[soundName] = std::move(buffer);
	soundMap[soundName] = new sf::Sound(soundBufferMap[soundName]);
}

void SoundManager::AddMusic(std::string musicName, std::string filePath)
{
	sf::Music *music = new sf::Music();

	if (!music->openFromFile(filePath))
	{
		throw std::runtime_error("Failed to Load Filepath: " + filePath);
	}
	musicMap[musicName] = std::move(music);
}