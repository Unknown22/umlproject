#include "OurSprite.h"
using namespace std;


OurSprite::OurSprite(string url)
{
	texture.loadFromFile(url);
	this->setTexture(texture);
	width = this->getTextureRect().width;
	height = this->getTextureRect().height;
	float xOrigin = (float)width / 2;
	float yOrigin = (float)height / 2;
	this->setOrigin(xOrigin, yOrigin);
}


OurSprite::~OurSprite()
{
}
