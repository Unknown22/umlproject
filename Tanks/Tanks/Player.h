#pragma once
#include "ScreenObject.h"
class Player :
	public ScreenObject
{
private:
	int hp;
	float vX, vY;

public:
	const int MAX_HP = 5;
	const int NORMAL_SPEED = 4;
	const int NORMAL_ROTATION_ANGLE = 3;
	Player();
	~Player();
	void gettingHit();
	void rotate(float angle);
	void setvX(float vX);
	float getvX();
	void setvY(float vY);
	float getvY();
};

