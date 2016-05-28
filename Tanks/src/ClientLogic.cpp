#include "ClientLogic.h"
#include <iostream>


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
						spriteMap.emplace(std::make_pair(std::string(objectSt[1]), SpriteClient("data//img//p2//playerDown.png", x, y, r)));
					}
					else
					{
						//std::cout << x<<" " <<  " "<< y <<  " "<< r<<endl;
						spriteMap.emplace(std::make_pair(std::string(objectSt[1]), SpriteClient("data//img//missile.png", x, y, r)));
					}
				}
				else if (objectSt[0] == "delete")
				{
					std::cout << objectSt[0]<< objectSt[1] << endl;
					spriteMap.erase(objectSt[1]);
				}
				else
				{
					float x = std::stof(objectSt[1]);
					float y = std::stof(objectSt[2]);
					float r = std::stof(objectSt[3]);
					if (objectSt[0] == "p1" || objectSt[0] == "p2")
					{
						std::string::size_type sz;   // alias of size_t

						int hp = std::stoi(objectSt[4], &sz);
						if (objectSt[0] == "p1")
						{
							//USTAW ¯YCIE p1 NA hp
							if (hp == 3) {
								spriteMap.emplace("hp1", SpriteClient("data//img//player_hp.png", 45.0, 45.0, 90.0));
								spriteMap.emplace("hp2", SpriteClient("data//img//gray_hp.png", 200, 312, 7));
								spriteMap.emplace("hp3", SpriteClient("data//img//player_hp.png", 80, 23, 8));
							}
							else if (hp == 2) {
								spriteMap.emplace(std::make_pair(std::string(objectSt[0]), SpriteClient("data//img//player_hp.png", 45.0, 45.0, 90.0)));
								spriteMap.emplace("hp2", SpriteClient("data//img//gray_hp.png", 200, 312, 0));
								spriteMap.emplace("hp3", SpriteClient("data//img//player_hp.png", 80, 23, 0));
							}
							else if (hp == 1) {
								spriteMap.emplace(std::make_pair(std::string(objectSt[0]), SpriteClient("data//img//player_hp.png", 45.0, 45.0, 90.0)));
								spriteMap.emplace("hp2", SpriteClient("data//img//gray_hp.png", 200, 312, 0));
								spriteMap.emplace("hp3", SpriteClient("data//img//player_hp.png", 80, 23, 0));

							}
							else {
								spriteMap.emplace(std::make_pair(std::string(objectSt[0]), SpriteClient("data//img//player_hp.png", 45.0, 45.0, 90.0)));
								spriteMap.emplace("hp2", SpriteClient("data//img//gray_hp.png", 200, 312, 0));
								spriteMap.emplace("hp3", SpriteClient("data//img//player_hp.png", 80, 23, 0));
							}
						}

						else if(objectSt[0] == "p2")
						{
							if (hp == 3) {
								spriteMap.emplace(std::make_pair(std::string(objectSt[0]), SpriteClient("data//img//player_hp.png", 45.0, 45.0, 90.0)));
								spriteMap.emplace("hp2", SpriteClient("data//img//gray_hp.png", 200, 312, 0));
								spriteMap.emplace("hp3", SpriteClient("data//img//player_hp.png", 80, 23, 0));
							}
							else if (hp == 2) {
								spriteMap.emplace(std::make_pair(std::string(objectSt[0]), SpriteClient("data//img//player_hp.png", 45.0, 45.0, 90.0)));
								spriteMap.emplace("hp2", SpriteClient("data//img//gray_hp.png", 200, 312, 0));
								spriteMap.emplace("hp3", SpriteClient("data//img//player_hp.png", 80, 23, 0));
							}
							else if (hp == 1) {
								spriteMap.emplace(std::make_pair(std::string(objectSt[0]), SpriteClient("data//img//player_hp.png", 45.0, 45.0, 90.0)));
								spriteMap.emplace("hp2", SpriteClient("data//img//gray_hp.png", 200, 312, 0));
								spriteMap.emplace("hp3", SpriteClient("data//img//player_hp.png", 80, 23, 0));

							}
							else {
								spriteMap.emplace(std::make_pair(std::string(objectSt[0]), SpriteClient("data//img//player_hp.png", 45.0, 45.0, 90.0)));
								spriteMap.emplace("hp2", SpriteClient("data//img//gray_hp.png", 200, 312, 0));
								spriteMap.emplace("hp3", SpriteClient("data//img//player_hp.png", 80, 23, 0));
							}
						}
					}
					
					spriteMap.at(objectSt[0]).setPosition(x, y);
					spriteMap.at(objectSt[0]).setRotation(r);
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

std::string ClientLogic::handleKeyboard(sf::Event event)
{
	
	using namespace std;
	string statement = "p";
	statement += std::to_string(whichClient);
	statement += ";";
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		statement += "up;";
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		statement += "down;";
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		statement += "left;";
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		statement += "right;";
	}
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Space && spacePressed==false)
		{
			spacePressed = true;
			statement += "space;";
		}
	}
	if (event.type == sf::Event::KeyReleased)
	{
		if (event.key.code == sf::Keyboard::Space)
			spacePressed = false;
	}
	//std::cout << statement<<endl;
	return statement;

}

ClientLogic::ClientLogic(int whichCl)
{
	whichClient = whichCl;
}


ClientLogic::~ClientLogic()
{
}


