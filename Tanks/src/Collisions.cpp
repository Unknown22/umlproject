#include "Collisions.h"

#include <iostream>


Collisions::Collisions()
{
	map=new tmx::TileMap("data//img//maps//test_map.tmx");
}


Collisions::~Collisions()
{
	delete map;
}

bool Collisions::checkCollision(float _x, float _y, int sprite_x, int sprite_y)
{

	
	bool colide = false;
	sf::FloatRect object(_x, _y, sprite_x, sprite_y);

	//std::cout << _x  << "    " <<  _y << std::endl;

	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			
			if (!map->GetLayer("collision").GetTile(i, j).empty())
			{
				sf::FloatRect collision_layer(i*32, j*32, 32, 32);

				if (collision_layer.intersects(object, result))
				{
					colide = true;
					//std::cout << "Colision! " << std::endl;
				}
			}

		}
	}

	return colide;
}

bool Collisions::checkMissle(float _x, float _y, float x, float y)
{
	bool colide = false;
	sf::FloatRect missle(_x, _y, 5, 5);

				sf::FloatRect player(x, y, 32, 32);

				if (player.intersects(missle, result))
				{
					colide = true;
					//std::cout << "Shot! " << std::endl;
				}

	return colide;
}
