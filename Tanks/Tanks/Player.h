#pragma once
#include "ScreenObject.h"
class Player :
	public ScreenObject
{
private:
	int hp, speed;

public:
	const int MAX_HP = 5;
	const int NORMAL_SPEED = 4;
	const int NORMAL_ROTATION_ANGLE = 2;
	Player();
	~Player();
	void gettingHit();
	void rotate(float angle);
};

