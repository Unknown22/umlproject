#include "Player.h"
#include <iostream>


Player::Player(float x, float y, float rotation)
{
	setX(x);
	setY(y);
	setRotation(rotation);
}

Player::Player()
{
	hp = MAX_HP;
	vX = 0;
	vY = 0; 
}


Player::~Player()
{
}

void Player::gettingHit()
{
	if (hp > 0)
		hp--;
	cout << "player hit!" << endl;
}

void Player::rotate(float angle)
{
	float rotation = getRotation();
	rotation += angle;
	setRotation(rotation);
}

void Player::setvX(float vX)
{
	this->vX = vX;
}

float Player::getvX()
{
	return vX;
}

void Player::setvY(float vY)
{
	this->vY = vY;
}

float Player::getvY()
{
	return vY;
}
