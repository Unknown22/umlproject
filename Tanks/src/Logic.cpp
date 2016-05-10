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
	p1.setX(440);
	p1.setY(50);
	p1.setRotation(0);
	string s = "spawn>p1>440>320>180;"; //stan poczatkowy, pozycja: x>y>rotation
	s += "spawn>p2>440>50>0";
	return s;
}

void Logic::listen(std::string statement)
{
	std::vector<std::string> elems;
	split(statement, ';', elems);
	p1.setvX(0);
	p1.setvY(0);
	p2.setvX(0);
	p2.setvY(0);
	if (elems.empty() == false)
	{
		if (elems[0] == "p1")
		{
			updatePlayer(elems, p1);
			handlePlayerUpdate(p1);
		}
		else if (elems[0] == "p2")
		{
			updatePlayer(elems, p2);
			handlePlayerUpdate(p2);
		}
		
		
		
	}
	handleMissilesUpdate();
}

string Logic::send()
{
	std::stringstream ss;
	ss << "p1>" << p1.getX() << ">" << p1.getY() << ">" << p1.getRotation() << ";";
	ss << "p2>" << p2.getX() << ">" << p2.getY() << ">" << p2.getRotation() << ";";
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

std::string Logic::shot(Player p)
{
	Missile missile(p.getX(), p.getY(), 0, 0);
	float missVX = -missile.NORMAL_SPEED * sin((p.getRotation()*M_PI) / 180.0f);
	float missVY = missile.NORMAL_SPEED * cos((p.getRotation()*M_PI) / 180.0f);
	missile.setvX(missVX);
	missile.setvY(missVY);
	missiles.push_back(missile);
	int id = missiles.size() - 1;
	std::stringstream ss;
	ss << "spawn>m" << id << ">" << missile.getX() << ">" << missile.getY() << ">" << 0 << ";";
	return ss.str();
}

void Logic::handlePlayerUpdate(Player& p)
{
	float x = p.getX();
	float y = p.getY();
	float rotation = p.getRotation();
	float vX = p.getvX();
	float vY = p.getvY();
	x += vX;
	y += vY;
	p.setX(x);
	p.setY(y);
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

void Logic::updatePlayer(std::vector<std::string>& elems, Player& p)
{
	for (int i = 1; i < elems.size(); i++)
	{
		//std::cout << elems[i];
		if (elems[i] == "up")
		{
			p.setvX(-p.NORMAL_SPEED * sin((p.getRotation()*M_PI) / 180.0f));
			p.setvY(p.NORMAL_SPEED * cos((p.getRotation()*M_PI) / 180.0f));
		}
		else if (elems[i] == "down")
		{
			p.setvX(p.NORMAL_SPEED * sin((p.getRotation()*M_PI) / 180.0f));
			p.setvY(-p.NORMAL_SPEED * cos((p.getRotation()*M_PI) / 180.0f));
		}
		else if (elems[i] == "left")
		{
			p.rotate(-p.NORMAL_ROTATION_ANGLE);
		}
		else if (elems[i] == "right")
		{
			p.rotate(p.NORMAL_ROTATION_ANGLE);
		}
		else if (elems[i] == "space")
		{
			addState = shot(p);
		}
	}
}
