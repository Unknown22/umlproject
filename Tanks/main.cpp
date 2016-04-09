#include <SFML/Graphics.hpp>
#include <enet/enet.h>
#include "multiplayer_network.h"
#include "OurSprite.h"
#include <iostream>


int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	OurSprite tank("img//p1//playerDown.png");//potrzeba 2 slashy
	shape.setFillColor(sf::Color::Green);

	
	tank.setPosition(100, 100);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down)
				tank.move(0, 1);
		}

		window.clear();
		window.draw(shape);
		window.draw(tank);
		window.display();
	}

	return 0;
}