#include <SFML/Graphics.hpp>
#include "playerController.h"
#include <iostream>


int main()
{
	const int WINDOW_WIDTH = 640;
	const int WINDOW_HEIGHT = 480;
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Tanks!");
	playerController p1("img//p1//playerDown.png");//potrzeba 2 slashe
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
		window.draw(p1);
		if (p1.missiles.empty() == false)
		{
			for (int i = 0; i < p1.missiles.size(); i++)
			{
				window.draw(*p1.missiles[i]);
			}
		}
		window.display();
	}

	return 0;
}