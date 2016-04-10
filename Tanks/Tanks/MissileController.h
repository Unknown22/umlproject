#pragma once
#include "OurSprite.h"
#include "Missile.h"
class MissileController :
	public OurSprite
{
private:
	Missile * missile;
public:
	MissileController(string url, float x, float y, float vX, float vY);
	~MissileController();
	void update();
};

