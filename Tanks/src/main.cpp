#include <SFML/Graphics.hpp>
#include "playerController.h"
#include <iostream>
#include "ConstantVariables.h"
#include "STP/TMXLoader.hpp"



int main()
{
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Tanks!");
	playerController p1("img//p1//playerDown.png");//potrzeba 2 slashe

	tmx::TileMap map("img//maps//test_map.tmx");
	map.ShowObjects();
	map.GetLayer("map").visible = true;
	map.GetLayer("collision").visible = false;




	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			
		}
		p1.handleKeyboardEvent();
		p1.update();

		window.clear();
		window.draw(map);
		window.draw(p1);



		if (p1.missiles.empty() == false)
		{
			for (int i = 0; i < p1.missiles.size(); i++)
			{
				window.draw(p1.missiles[i]);
			}
		}
		window.display();
	}

	return 0;
}