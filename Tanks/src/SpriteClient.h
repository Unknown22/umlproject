#pragma once
#include "OurSprite.h";
class SpriteClient :
	public OurSprite
{
private:

public:
	SpriteClient(string url, float x, float y, float rotation);
	SpriteClient::SpriteClient(const SpriteClient& other);
	~SpriteClient();
	void update(float x, float y, float rotation);
};

