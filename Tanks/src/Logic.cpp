#include "Logic.h"
#include <iostream>
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
	string s = "spawn>p1>440>320>180;"; //stan poczatkowy, pozycja: x>y>rotation
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
				addState=shot();
			}
			handlePlayerUpdate();
		}
	}
	handleMissilesUpdate();
}

string Logic::send()
{
	std::stringstream ss;
	ss << "p1>" << p1.getX() << ">" << p1.getY() << ">" << p1.getRotation() << ";";
	if (addState.empty() == false)
	{
		ss << addState;
	}
		
	addState.erase();
	if (missiles.empty() == false)
	{
		for (int i = 0; i < missiles.size(); i++)
		{
			ss << "m" << i << ">" << missiles[i].getX() << ">" << missiles[i].getY() << ">" << 0 << ";";
		}
	}
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

std::string Logic::shot()
{
	Missile missile(p1.getX(), p1.getY(), 0, 0);
	float missVX = -missile.NORMAL_SPEED * sin((p1.getRotation()*M_PI) / 180.0f);
	float missVY = missile.NORMAL_SPEED * cos((p1.getRotation()*M_PI) / 180.0f);
	missile.setvX(missVX);
	missile.setvY(missVY);
	missiles.push_back(missile);
	int id = missiles.size() - 1;
	std::stringstream ss;
	ss << "spawn>m" << id << ">" << missile.getX() << ">" << missile.getY() << ">" << 0 << ";";
	return ss.str();
}

void Logic::handlePlayerUpdate()
{
	float x = p1.getX();
	float y = p1.getY();
	float rotation = p1.getRotation();
	float vX = p1.getvX();
	float vY = p1.getvY();
	x += vX;
	y += vY;
	p1.setX(x);
	p1.setY(y);
	//std::cout << x << " " << y << endl;
}

void Logic::handleMissilesUpdate()
{
	if (missiles.empty() == false)
	{
		for (int i = 0; i < missiles.size(); i++)
		{
			missiles[i].update();
		}
		for (int i = 0; i < missiles.size(); i++)
		{

			if (missiles[i].isInactive() == true)
			{
				missiles.erase(missiles.begin() + i);
			}

		}
	}
}
