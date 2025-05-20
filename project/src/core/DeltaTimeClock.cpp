#include "core/DeltaTimeClock.h"

DeltaTimeClock *DeltaTimeClock::instance = nullptr;
float DeltaTimeClock::deltaTime = 0.f;

DeltaTimeClock::DeltaTimeClock() {}

DeltaTimeClock::~DeltaTimeClock()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

DeltaTimeClock *DeltaTimeClock::GetInstance()
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

float DeltaTimeClock::GetDeltaTime()
{
	return deltaTime;
}

void DeltaTimeClock::update()
{
	deltaTime = deltaClock.restart().asSeconds();
}
