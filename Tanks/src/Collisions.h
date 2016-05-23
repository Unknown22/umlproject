#pragma once
#include "SFML\Graphics\Rect.hpp"

class Collisions
{
public:
	Collisions();
	~Collisions();
	sf::FloatRect result;
	bool checkCollision(float _x, float _y, int sprite_x, int sprite_y);
	bool checkMissle(float _x, float _y, float x, float y);
};


