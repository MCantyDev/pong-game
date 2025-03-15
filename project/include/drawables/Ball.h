#ifndef BALL_H
#define BALL_H

// Singletons
#include "RenderWindowManager.h"
#include "DeltaTimeClock.h"
#include "SoundManager.h"
#include "ScoreManager.h"

// Drawables
#include "drawables/Drawable.h"

// Observable
#include "Observer/Observable.h"

// SFML Include
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

// Standard Library Include
#include <random>
#include <cmath>

class Paddle;

class Ball : public Drawable, public Observable<PaddleSide>
{
public:
	Ball(Paddle* p1, Paddle* p2);

	// Update Function
	void update();


	// Pure Virtual Functions from Drawable
	virtual float getTop() const override;
	virtual float getBottom() const override;
	virtual float getFront() const override;
	virtual float getBack() const override;

private:
	// Collision Check Functions
	void paddleCollisionCheck();
	void wallCollisionCheck();
	void scoreCollisionCheck();

	ScoreManager* scoreManager = nullptr;

	sf::CircleShape circle;
	float ballRadius = 15.f;
	float ballSpeed = 600.f;
	sf::Angle ballAngle;

	Paddle* playerOne = nullptr;
	Paddle* playerTwo = nullptr;

	sf::Clock delayClock;
	bool moveBall = false;

	// Random Number Generator
	std::random_device rando;
	std::mt19937 rng;
};

#endif // BALL_H