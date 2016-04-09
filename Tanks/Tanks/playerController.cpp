#include "playerController.h"



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
	this->setPosition(x, y);
	this->setRotation(rotation);
}

void playerController::handleKeyboardEvent(sf::Event event)
{
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left)
		player.rotate(-player.NORMAL_ROTATION_ANGLE);
	if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right)
		player.rotate(player.NORMAL_ROTATION_ANGLE);
}
