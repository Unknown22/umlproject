#include "Logic.h"
#define M_PI       3.14159265358979323846


Logic::Logic()
{
}


Logic::~Logic()
{
}

string Logic::init()
{
	p1.setX(440);
	p1.setY(320);
	p1.setRotation(180);
	string s = "spawn>p1>440;320;180"; //stan poczatkowy, pozycja: x;y;rotation
	return s;
}

void Logic::listen(std::string statement)
{
	std::vector<std::string> elems;
	split(statement, ';', elems);
	p1.setvX(0);
	p1.setvY(0);
	if (elems.empty() == false)
	{
		for (int i = 0; i < elems.size(); i++)
		{
			if (elems[i] == "up")
			{
				p1.setvX(-p1.NORMAL_SPEED * sin((p1.getRotation()*M_PI) / 180.0f));
				p1.setvY(p1.NORMAL_SPEED * cos((p1.getRotation()*M_PI) / 180.0f));
			}
			else if (elems[i] == "down")
			{
				p1.setvX(p1.NORMAL_SPEED * sin((p1.getRotation()*M_PI) / 180.0f));
				p1.setvY(-p1.NORMAL_SPEED * cos((p1.getRotation()*M_PI) / 180.0f));
			}
			else if (elems[i] == "left")
			{
				p1.rotate(-p1.NORMAL_ROTATION_ANGLE);
			}
			else if (elems[i] == "right")
			{
				p1.rotate(p1.NORMAL_ROTATION_ANGLE);
			}
			else if (elems[i] == "space")
			{
				//obsluga dla strzelania
			}
		}
	}
}

string Logic::send()
{
	std::stringstream ss;
	ss << "p1<" << p1.getX() << ";" << p1.getY() << ";" << p1.getRotation();
	//tutaj dodanie p2 i wszystich pocisków
	return ss.str();;
}

std::vector<std::string>& Logic::split(const std::string & s, char delim, std::vector<std::string>& elems)
{
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}