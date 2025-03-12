#include "DeltaTimeClock.h"

DeltaTimeClock* DeltaTimeClock::instance = nullptr;
float DeltaTimeClock::deltaTime = 0.f;

DeltaTimeClock::DeltaTimeClock() {}

DeltaTimeClock* DeltaTimeClock::GetInstance()
{
	if (!instance)
	{
		instance = new DeltaTimeClock();
	}
	return instance;
}

void DeltaTimeClock::DeleteInstance()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

void DeltaTimeClock::update()
{
	deltaTime = deltaClock.restart().asSeconds();
}

float DeltaTimeClock::getDeltaTime()
{
	return deltaTime;
}