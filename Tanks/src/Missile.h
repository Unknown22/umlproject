#pragma once
#include "ScreenObject.h"
class Missile :
	public ScreenObject
{
private:
	float vX, vY;
public:
	const float NORMAL_SPEED=0.02f;
	Missile(float x, float y, float vX, float vY);
	Missile(Missile &);
	~Missile();
	void setvX(float vX);
	float getvX();
	void setvY(float vY);
	float getvY();
};

