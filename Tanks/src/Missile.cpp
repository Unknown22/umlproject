#include "Missile.h"
#include "ConstantVariables.h"


Missile::Missile(float x, float y, float vX, float vY)
{
	setRotation(0);
	setX(x);
	setY(y);
	this->vX = vX;
	this->vY = vY;
}

Missile & Missile::operator=(const Missile & otherMissile)
{
	this->vX = otherMissile.vX;
	this->vY = otherMissile.vY;
	this->setX(otherMissile.x);
	this->setY(otherMissile.y);
	return *this;
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

bool Missile::isInactive()
{
	int x = getX();
	int y = getY();
	if (collisions.checkCollision(x,y,5,5))
		return true;
	else
		return false;
}

void Missile::update()
{
	float x = getX();
	float y = getY();
	float vX = getvX();
	float vY = getvY();
	x += vX;
	y += vY;
	setX(x);
	setY(y);
}
