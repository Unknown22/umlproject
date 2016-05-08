#pragma once
#include "Player.h"
#include <string>
#include <sstream>
#include <vector>
class Logic
{
public:
	Logic();
	~Logic();
	string init();
	void listen(std::string statement);
	string send();
	std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
private:
	Player p1, p2;
};

