#include "handleKeyboard.h"
//#include <iostream>
using namespace std;

string handleKeyboard()
{
	string statement="";
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