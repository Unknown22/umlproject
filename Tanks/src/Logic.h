#pragma once
#include "Player.h"
#include <string>
#include <sstream>
#include <vector>
#include "missile.h"
#include "Collisions.h"
class Logic
{
public:
	Logic();
	~Logic();
	string init();
	void listen(std::string statement);
	string send();
	std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
	map<string, Missile> missiles;
	std::string shot(Player& p);
private:
	Player p1, p2;
	Collisions collisions;
	void handlePlayerUpdate(Player& p);
	void handleMissilesUpdate(Player& p);
	void updatePlayer(std::vector<std::string> &elems, Player& p);
	string addState;
	sf::Clock Clock;
	sf::Time time;
};

