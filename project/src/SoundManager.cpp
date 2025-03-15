#include "SoundManager.h"

// Static Values
SoundManager* SoundManager::instance = nullptr;

std::unordered_map<std::string, sf::SoundBuffer> SoundManager::soundBufferMap;
std::unordered_map<std::string, sf::Sound*> SoundManager::soundMap;
std::unordered_map<std::string, sf::Music*> SoundManager::musicMap;


SoundManager::~SoundManager()
{
	// Delete all Sound Resources (as Raw Pointers used)
	for (auto& sound : soundMap)
	{
		delete sound.second;
		sound.second = nullptr;
	}

	// Delete all Music Resources (as Raw Pointers used)
	for (auto& music : musicMap)
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

SoundManager* SoundManager::GetInstance()
{
	if (!instance)
		instance = new SoundManager();

	return instance;
}

sf::Sound* SoundManager::GetSound(std::string soundName)
{
	auto it = soundMap.find(soundName);
	if (it != soundMap.end())
	{
		return it->second;
	}

	throw std::runtime_error("Sound not found: " + soundName);
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

sf::Music* SoundManager::GetMusic(std::string musicName)
{
	auto it = musicMap.find(musicName);
	if (it != musicMap.end())
	{
		return it->second;
	}

	throw std::runtime_error("Music not found: " + musicName);
}
void SoundManager::AddMusic(std::string musicName, std::string filePath)
{
	sf::Music* music = new sf::Music();

	if (music->openFromFile(filePath))
	{
		musicMap[musicName] = std::move(music);
	}
}