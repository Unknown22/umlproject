#include "SpriteClient.h"




SpriteClient::SpriteClient(string url, float x, float y, float rotation)
	:OurSprite(url)
{
	setPosition(x, y);
	setRotation(rotation);
}

SpriteClient::SpriteClient(const SpriteClient & other)
	:OurSprite(other)
{

}


SpriteClient::~SpriteClient()
{
}

void SpriteClient::update(float x, float y, float rotation)
{
	setPosition(x, y);
	setRotation(rotation);
}