#include <SFML/Graphics.hpp>
#include <enet/enet.h>
#include "multiplayer_network.h"
#include "playerController.h"
#include <iostream>


int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 480), "Tanks!");
	playerController p1("img//p1//playerDown.png");//potrzeba 2 slashe

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			p1.handleKeyboardEvent();
			p1.update();
		}

		window.clear();
		window.draw(p1);
		window.display();
	}

	return 0;
}