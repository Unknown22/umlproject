#include "ScreenObject.h"



ScreenObject::ScreenObject()
{
}

ScreenObject::~ScreenObject()
{
}

void ScreenObject::setX(int x)
{
	this->x = x;
}

void ScreenObject::setY(int y)
{
	this->y = y;
}

int ScreenObject::getX()
{
	return x;
}

int ScreenObject::getY()
{
	return y;
}

void ScreenObject::setRotation(int angle)
{
	this->rotation = angle;
}

int ScreenObject::getRotation()
{
	return rotation;
}



