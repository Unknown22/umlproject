#pragma once
#include "ScreenObject.h"
#include "Collisions.h"

class Missile :
	public ScreenObject
{
private:
	float vX, vY, x, y;
	Collisions collisions;

public:
	const float NORMAL_SPEED=8.5f;
	Missile(float x, float y, float vX, float vY);
	Missile & operator=(const Missile & otherMissile);
	~Missile();
	void setvX(float vX);
	float getvX();
	void setvY(float vY);
	float getvY();
	bool isInactive();
	void update();
};

