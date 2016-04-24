#pragma once
#include "ScreenObject.h"
#include "MissileController.h"
#include <list>
class Player :
	public ScreenObject
{
private:
	int hp;
	float vX, vY;
	std::list<MissileController> missiles;

public:
	const int MAX_HP = 5;
	const float NORMAL_SPEED = 0.1;
	const float NORMAL_ROTATION_ANGLE = 0.1;
	Player();
	~Player();
	void gettingHit();
	void rotate(float angle);
	void setvX(float vX);
	float getvX();
	void setvY(float vY);
	float getvY();
	void shot(Missile & miss);
	int getNumberOfMissiles();
	std::list<MissileController> getMissiles();
};

