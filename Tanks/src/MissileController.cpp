#include "MissileController.h"




MissileController::MissileController(string url, float x, float y, float vX, float vY)
	: OurSprite(url)
{
	this->setPosition(x, y);
}


MissileController::~MissileController()
{
}

void MissileController::update()
{
	this->move(getvX(), getvY());
}
void MissileController::setvX(float vX)
{
	this->vX = vX;
}

float MissileController::getvX()
{
	return vX;
}

void MissileController::setvY(float vY)
{
	this->vY = vY;
}

float MissileController::getvY()
{
	return vY;
}
