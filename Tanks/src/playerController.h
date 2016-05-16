#pragma once
#include "OurSprite.h"
#include "Player.h"


class playerController :
	public OurSprite
{
private:
	Player player;
	void handlePlayerUpdate();
	void handleMissilesUpdate();

public:
	std::vector<MissileController> missiles;
	playerController(string url);
	~playerController();
	void update();
	void handleKeyboardEvent();
	//std::vector<MissileController> * getMissiles();
};

