#include "Logic.h"
#include <iostream>
#include <Time.h>
#define M_PI       3.14159265358979323846


Logic::Logic()
{
}


Logic::~Logic()
{
}

string Logic::init()
{
	p1.setX(100);
	p1.setY(320);
	p1.setRotation(180);
	p2.setX(440);
	p2.setY(50);
	p2.setRotation(0);
	p1.setHp(3);
	p2.setHp(3);
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
			handleMissilesUpdate(p2);

		}
		else if (elems[0] == "p2")
		{
			updatePlayer(elems, p2);
			handlePlayerUpdate(p2);	
			handleMissilesUpdate(p1);

		}
	}

}

string Logic::send()
{
	std::stringstream ss;
	ss << "p1>" << p1.getX() << ">" << p1.getY() << ">" << p1.getRotation() << ">" << p1.getHp() << ";";
	ss << "p2>" << p2.getX() << ">" << p2.getY() << ">" << p2.getRotation() << ">" << p2.getHp() << ";";
	if (addState.empty() == false)
	{
		ss << addState;
	}
		
	addState.erase();
	if (missiles.empty() == false)
	{
		typedef std::map<std::string, Missile>::iterator it_type;
		for (it_type iterator = missiles.begin(); iterator != missiles.end(); iterator++) {
			ss <<"m"<< iterator->first << ">" << iterator->second.getX() << ">" << iterator->second.getY() << ">" << 0 << ";";
		}
	}
	std::cout << ss.str() << endl;
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

std::string Logic::shot(Player& p)
{
	int id = missiles.size();
	string ids = std::to_string(id);
	missiles.emplace(std::make_pair(std::string(std::to_string(id)), Missile(p.getX(), p.getY(), 0, 0)));
	float missVX = -missiles.at(ids).NORMAL_SPEED * sin((p.getRotation()*M_PI) / 180.0f);
	float missVY = missiles.at(ids).NORMAL_SPEED * cos((p.getRotation()*M_PI) / 180.0f);
	missiles.at(ids).setvX(missVX);
	missiles.at(ids).setvY(missVY);
	std::stringstream ss;
	ss << "spawn>m" << id << ">" << missiles.at(ids).getX() << ">" << missiles.at(ids).getY() << ">" << 0 << ";";
	//std::cout << ss.str() << endl;
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
}

void Logic::handleMissilesUpdate(Player& p)
{
	if (missiles.empty() == false)
	{
		typedef std::map<std::string, Missile>::iterator it_type;
		it_type iterator = missiles.begin();
		it_type iterator_shot = missiles.begin();

		while (iterator != missiles.end())
		{
			if (iterator->second.isInactive() == true)
			{
				std::stringstream ss;
				ss << "delete>m" << iterator->first << ";";
				missiles.erase(iterator);
				addState += ss.str();
				std::cout << addState << endl;
				iterator = missiles.begin();

			}
			else if (collisions.checkMissle(iterator->second.getX(), iterator->second.getY(), p.getX(), p.getY()))
			{
				p.gettingHit();
				std::stringstream ss;
				ss << "delete>m" << iterator->first << ";";
				missiles.erase(iterator);
				addState += ss.str();
				std::cout << addState << endl;
				iterator = missiles.begin();
			}
			else
			{
				++iterator;
			}
		}				
	}

		typedef std::map<std::string, Missile>::iterator it_type;
		for (it_type iterator = missiles.begin(); iterator != missiles.end(); iterator++) {
			iterator->second.update();
		}
}


void Logic::updatePlayer(std::vector<std::string>& elems, Player& p)
{
	for (int i = 1; i < elems.size(); i++)
	{
		//std::cout << elems[i];
		if (elems[i] == "up")
		{
			float x1 = p.getX();
			float y1 = p.getY();
			if (!collisions.checkCollision( x1 + -p.NORMAL_SPEED * sin((p.getRotation()*M_PI) / 180.0f), y1 + p.NORMAL_SPEED * cos((p.getRotation()*M_PI) / 180.0f), 10, 10)) 
			{
				p.setvX(-p.NORMAL_SPEED * sin((p.getRotation()*M_PI) / 180.0f));
				p.setvY(p.NORMAL_SPEED * cos((p.getRotation()*M_PI) / 180.0f));
			}

		}
		else if (elems[i] == "down")
		{
			float x2 = p.getX();
			float y2 = p.getY();
			if (!collisions.checkCollision(x2 + p.NORMAL_SPEED * sin((p.getRotation()*M_PI) / 180.0f), y2 + -p.NORMAL_SPEED * cos((p.getRotation()*M_PI) / 180.0f), 10, 10))
			{
				p.setvX(p.NORMAL_SPEED * sin((p.getRotation()*M_PI) / 180.0f));
				p.setvY(-p.NORMAL_SPEED * cos((p.getRotation()*M_PI) / 180.0f));
			}

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
			addState += shot(p);

		}
	}
}
