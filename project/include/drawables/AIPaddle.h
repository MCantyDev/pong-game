#ifndef AIPADDLE_H
#define AIPADDLE_H

#include "drawables/Paddle.h"

class AiPaddle : public Paddle
{
public:
	AiPaddle(PaddleSide side);

	void setObject(Drawable *object);
	void update();

private:
	void calcSpeed(Drawable *object);

	// Private Variables
	sf::Clock computerClock;
	sf::Time computerTime = sf::milliseconds(1);

	Drawable *object = nullptr;
};

#endif // AIPADDLE_H