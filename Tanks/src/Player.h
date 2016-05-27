#pragma once
#include "ScreenObject.h"
#include "MissileController.h"
class Player :
	public ScreenObject
{
private:
	int hp;
	float vX, vY;

public:
	const int MAX_HP = 5;
	const float NORMAL_SPEED = 2.0f;
	const float NORMAL_ROTATION_ANGLE = 3.5f;
	Player(float x, float y, float rotation);
	Player();
	~Player();
	void setHp(int _hp);
	int getHp();
	void gettingHit();
	void rotate(float angle);
	void setvX(float vX);
	float getvX();
	void setvY(float vY);
	float getvY();
};

