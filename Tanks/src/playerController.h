#pragma once
#include "OurSprite.h"
#include "Player.h"
class playerController :
	public OurSprite
{
private:
	Player player;
	void handleMissilesUpdate();
public:
	playerController(string url);
	~playerController();
	void update();
	void handleKeyboardEvent();
};

