#include "MissileController.h"




MissileController::MissileController(string url, float x, float y, float vX, float vY)
	: OurSprite(url)
{
	missile=new Missile(x, y, vX, vY);
	this->setPosition(x, y);
}

MissileController::MissileController(string url, Missile & miss)
	: OurSprite(url),
	missile(&miss)
{
	this->setPosition(missile->getX(), missile->getY());
}

MissileController::~MissileController()
{
	//delete missile;
}

void MissileController::update()
{
	float x = missile->getX();
	float y = missile->getY();
	float vX = missile->getvX();
	float vY = missile->getvY();
	x += vX;
	y += vY;
	missile->setX(x);
	missile->setY(y);
	this->move(vX, vY);
}
