#pragma once
#include <SFML/Graphics.hpp>
using namespace std;

class OurSprite : public sf::Sprite
{
	
public:
	OurSprite(string url);
	~OurSprite();
	int getWidth();
	int getHeight();

private:
	sf::Texture texture;
	int width, height;
};

