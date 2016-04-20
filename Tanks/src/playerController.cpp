#include "playerController.h"
#define M_PI       3.14159265358979323846


playerController::playerController(string url) 
	: OurSprite(url)
{

}


playerController::~playerController()
{
}

void playerController::update()
{
	float x = player.getX();
	float y = player.getY();
	float rotation = player.getRotation();
	float vX = player.getvX();
	float vY = player.getvY();
	x += vX;
	y += vY;
	player.setX(x);
	player.setY(y);
	this->move(vX, vY);
	this->setRotation(rotation);
}

void playerController::handleKeyboardEvent()
{
	player.setvX(0);
	player.setvY(0);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		player.setvX(-player.NORMAL_SPEED * sin((player.getRotation()*M_PI) / 180.0f));
		player.setvY(player.NORMAL_SPEED * cos((player.getRotation()*M_PI) / 180.0f));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		player.setvX(player.NORMAL_SPEED * sin((player.getRotation()*M_PI) / 180.0f));
		player.setvY(-player.NORMAL_SPEED * cos((player.getRotation()*M_PI) / 180.0f));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		player.rotate(-player.NORMAL_ROTATION_ANGLE);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		player.rotate(player.NORMAL_ROTATION_ANGLE);
}
