#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

// SFML Include
#include "SFML/Audio.hpp"

// Custom Include
#include "GameEnums.h"

// Standard Library Include
#include <string>
#include <unordered_map>

/**
 * @class SoundManager
 * @brief Singleton class for managing sound effects and music in the Pong game.
 *
 * Handles loading and retrieval of sound effects and background music using SFML.
 * Sounds and music are identified and accessed via string keys.
 */
class SoundManager
{
public:
	/**
	 * @brief Destructor to clean up loaded sounds and music.
	 */
	~SoundManager();

	/**
	 * @brief Retrieves the singleton instance of the SoundManager.
	 * @return Pointer to the SoundManager instance.
	 */
	static SoundManager *GetInstance();

	/**
	 * @brief Deletes the singleton instance, freeing allocated resources.
	 */
	static void DeleteInstance();

	/**
	 * @brief Play a Sound Effect or Music track.
	 * @param name key to associate with loaded sound effect or music.
	 * @param type of sound retreived - Sound::Effect - Sound::Music
	 */
	static void Play(std::string name, Sound type);

	/**
	 * @brief Pause a Sound Effect or Music track.
	 * @param name key to associate with loaded sound effect or music.
	 * @param type of sound retreived - Sound::Effect - Sound::Music
	 */
	static void Pause(std::string name, Sound type);

	/**
	 * @brief Loads a sound file and stores it with the given name.
	 * @param soundName Key to associate with the loaded sound.
	 * @param filePath Path to the sound file to load.
	 *
	 * Internally stores both the sound buffer and the sf::Sound object.
	 */
	static void AddSound(std::string soundName, std::string filePath);

	/**
	 * @brief Loads a music file and stores it with the given name.
	 * @param musicName Key to associate with the loaded music.
	 * @param filePath Path to the music file to load.
	 */
	static void AddMusic(std::string musicName, std::string filePath);

	/**
	 * @brief Retrieves a pointer to a loaded sound by name.
	 * @param soundName The name/key of the sound.
	 * @return Pointer to the corresponding sf::Sound object, or nullptr if not found.
	 */
	static sf::Sound *getSound(std::string soundName);

	/**
	 * @brief Retrieves a pointer to a loaded music track by name.
	 * @param musicName The name/key of the music.
	 * @return Pointer to the corresponding sf::Music object, or nullptr if not found.
	 */
	static sf::Music *getMusic(std::string musicName);

private:
	SoundManager() = default;
	static SoundManager *instance;

	static std::unordered_map<std::string, sf::SoundBuffer> soundBufferMap;
	static std::unordered_map<std::string, sf::Sound *> soundMap;
	static std::unordered_map<std::string, sf::Music *> musicMap;

	// Copy Constructors
	SoundManager(const SoundManager &) = delete;
	SoundManager &operator=(const SoundManager &) = delete;
};

#endif // SOUNDMANAGER_H