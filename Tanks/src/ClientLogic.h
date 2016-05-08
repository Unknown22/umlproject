#pragma once
#include "SFML\Window\Keyboard.hpp"
#include <string>
#include <sstream>
#include <vector>
#include "SpriteClient.h"

class ClientLogic
{
	
public:
	SpriteClient p1;
	void listen(std::string statement);
	std::vector<std::string>& ClientLogic::split(const std::string & s, char delim, std::vector<std::string>& elems);
	std::string handleKeyboard();
	ClientLogic();
	~ClientLogic();
};

