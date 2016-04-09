#include "OurSprite.h"
using namespace std;


OurSprite::OurSprite(string url)
{
	texture.loadFromFile(url);
	this->setTexture(texture);
}


OurSprite::~OurSprite()
{
}
