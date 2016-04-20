#pragma once
#include "ScreenObject.h"
class Missile :
	public ScreenObject
{
private:
	float vX, vY;
public:
	const int NORMAL_SPEED = 8;
	Missile(float x, float y, float vX, float vY);
	~Missile();
	void setvX(float vX);
	float getvX();
	void setvY(float vY);
	float getvY();
};

