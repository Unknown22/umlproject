#pragma once
#include "OurSprite.h"
class MissileController :
	public OurSprite
{
private:
	float vX, vY;
public:
	MissileController(string url, float x, float y, float vX, float vY);
	MissileController & operator=(const MissileController & otherMissile);
	const float NORMAL_SPEED = 0.4f;
	virtual ~MissileController();
	void update();
	void setvX(float vX);
	float getvX();
	void setvY(float vY);
	float getvY();
	bool isInactive();
};

