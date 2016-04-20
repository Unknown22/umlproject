#include "ScreenObject.h"



ScreenObject::ScreenObject()
{
	this->x = 30;
	this->y = 30;
	this->rotation = 0;
}

ScreenObject::~ScreenObject()
{
}

void ScreenObject::setX(float x)
{
	this->x = x;
}

void ScreenObject::setY(float y)
{
	this->y = y;
}

float ScreenObject::getX()
{
	return x;
}

float ScreenObject::getY()
{
	return y;
}

void ScreenObject::setRotation(float angle)
{
	this->rotation = angle;
}

float ScreenObject::getRotation()
{
	return rotation;
}



