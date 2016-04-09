#pragma once
#include "OurSprite.h"
#include "Player.h"
class playerController :
	public OurSprite
{
private:
	Player player;
public:
	playerController(string url);
	~playerController();
	void update();
	void handleKeyboardEvent();
};

