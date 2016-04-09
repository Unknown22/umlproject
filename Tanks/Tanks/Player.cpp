#include "Player.h"



Player::Player()
{
	hp = MAX_HP;
	speed = NORMAL_SPEED;
}


Player::~Player()
{
}

void Player::gettingHit()
{
	if (hp > 0)
		hp--;
}

void Player::rotate(float angle)
{
	int rotation = getRotation();
	rotation += angle;
	setRotation(rotation);
}
