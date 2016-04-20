#include "Missile.h"



Missile::Missile(float x, float y, float vX, float vY)
{
	setRotation(0);
	setX(x);
	setY(y);
	this->vX = vX;
	this->vY = vY;
}


Missile::~Missile()
{
}

void Missile::setvX(float vX)
{
	this->vX = vX;
}

float Missile::getvX()
{
	return vX;
}

void Missile::setvY(float vY)
{
	this->vY = vY;
}

float Missile::getvY()
{
	return vY;
}
