#include "OurSprite.h"
using namespace std;

sf::Texture texture;

OurSprite::OurSprite(string url)
{
	texture.loadFromFile(url);
	this->setTexture(texture);
}


OurSprite::~OurSprite()
{
}
