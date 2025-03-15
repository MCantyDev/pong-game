#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

// SFML Include
#include "SFML/Audio.hpp"

// Standard Library Include
#include <string>
#include <unordered_map>

class SoundManager
{
public:
	~SoundManager();

	static SoundManager* GetInstance();
	static sf::Sound* GetSound(std::string soundName);
	static sf::Music* GetMusic(std::string musicName);

	static void AddSound(std::string soundName, std::string filePath);
	static void AddMusic(std::string soundName, std::string filePath);

private:
	SoundManager() = default;
	static SoundManager* instance;

	static std::unordered_map<std::string, sf::SoundBuffer> soundBufferMap;
	static std::unordered_map<std::string, sf::Sound*> soundMap;

	static std::unordered_map<std::string, sf::Music*> musicMap;

	// Copy Constructors
	SoundManager(const SoundManager&) = delete;
	SoundManager& operator=(const SoundManager&) = delete;
};

#endif // SOUNDMANAGER_H