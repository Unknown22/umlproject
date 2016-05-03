#include "MissileController.h"
#include "ConstantVariables.h"



MissileController::MissileController(string url, float x, float y, float vX, float vY)
	: OurSprite(url)
{
	this->setPosition(x, y);
	this->vX = vX;
	this->vY = vY;
}



MissileController & MissileController::operator=(const MissileController & otherMissile)
{
	return *this;
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

bool MissileController::isInactive()
{
	int x = this->getPosition().x;
	int y = this->getPosition().y;
	if (x < 0 || y < 0)
		return true;
	else if (x > WINDOW_WIDTH || y>WINDOW_HEIGHT)
		return true;
	else
		return false;
}


