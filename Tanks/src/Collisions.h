#pragma once
#include "SFML\Graphics\Rect.hpp"

class Collisions
{
public:
	Collisions();
	~Collisions();
	sf::FloatRect result;
	bool checkCollision(float _x, float _y, int sprite_x, int sprite_y);
};


