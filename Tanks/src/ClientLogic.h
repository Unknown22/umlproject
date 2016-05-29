#pragma once
#include "SFML\Window\Keyboard.hpp"
#include <string>
#include <sstream>
#include <vector>
#include "SpriteClient.h"
#include <map>

class ClientLogic
{

public:
	map<string, SpriteClient> spriteMap;
	int whichClient;
	//SpriteClient p1;
	int listen(std::string statement);
	std::vector<std::string>& ClientLogic::split(const std::string & s, char delim, std::vector<std::string>& elems);
	std::string handleKeyboard(sf::Event event);
	ClientLogic(int whichCl);
	~ClientLogic();
private:
	bool spacePressed = false;
};

