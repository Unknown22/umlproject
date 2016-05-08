#include "ClientLogic.h"



void ClientLogic::listen(std::string statement)
{
	std::vector<std::string> elems;
	split(statement, ';', elems);
	if (elems.empty() == false)
	{
		for (int i = 0; i < elems.size(); i++)
		{
			std::vector<std::string> objectSt;
			split(elems[i], '>', objectSt);
			if (objectSt.empty() == false)
			{
				if (objectSt[0] == "spawn")
				{
					float x = std::stof(objectSt[2]);
					float y = std::stof(objectSt[3]);
					float r = std::stof(objectSt[4]);
					if (objectSt[1] == "p1")
					{
						//SpriteClient sprCl("data//img//p1//playerDown.png", x, y, r);
						spriteMap.emplace(std::make_pair(std::string(objectSt[1]), SpriteClient("data//img//p1//playerDown.png", x, y, r)));
					}
					else if(objectSt[1] == "p2")
					{

					}
					else
					{

					}
				}
				else if (objectSt[0] == "delete")
				{

				}
				else
				{
					float x = std::stof(objectSt[1]);
					float y = std::stof(objectSt[2]);
					float r = std::stof(objectSt[3]);
					typedef std::map<std::string, SpriteClient>::iterator it_type;
					for (it_type iterator = spriteMap.begin(); iterator != spriteMap.end(); iterator++) {
						iterator->second.setPosition(x, y);
						iterator->second.setRotation(r);
					}
				}
			}
		}
	}
}

std::vector<std::string>& ClientLogic::split(const std::string & s, char delim, std::vector<std::string>& elems)
{
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}

std::string ClientLogic::handleKeyboard()
{
	
	using namespace std;
	string statement = "";
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		statement += "up";
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		statement += "down";
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (statement.empty() == false)
			statement += ";";
		statement += "left";
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (statement.empty() == false)
			statement += ";";
		statement += "right";
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (statement.empty() == false)
			statement += ";";
		statement += "space";
	}
	//std::cout << statement;
	return statement;

}

ClientLogic::ClientLogic()
{

}


ClientLogic::~ClientLogic()
{
}


