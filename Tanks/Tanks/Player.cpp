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
