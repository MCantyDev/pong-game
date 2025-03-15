#ifndef DELTATIMECLOCK_H
#define DELTATIMECLOCK_H

// SFML Include 
#include "SFML/System.hpp"

class DeltaTimeClock
{
public:
	static DeltaTimeClock* GetInstance();
	static void DeleteInstance();

	static float GetDeltaTime();

	void update();

private:
	DeltaTimeClock();
	static DeltaTimeClock* instance;

	// Prevent Copying
	DeltaTimeClock(const DeltaTimeClock&) = delete;
	DeltaTimeClock& operator=(const DeltaTimeClock&) = delete;

	sf::Clock deltaClock;
	static float deltaTime;
};

#endif // DELTATIMECLOCK_H