#pragma once
#include "ScreenObject.h"
class Player :
	public ScreenObject
{
private:
	const int MAX_HP = 5;
	const int NORMAL_SPEED = 4;
	int hp, speed;

public:
	Player();
	~Player();
	void gettingHit();
};

