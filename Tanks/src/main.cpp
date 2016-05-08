#include <SFML/Graphics.hpp>
#include "playerController.h"
#include <iostream>
#include "ConstantVariables.h"
#include "STP/TMXLoader.hpp"
#include <string>

sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Tanks!");
enum GameState { MENU, GAME_CREATE, GAME_JOIN, GAME_OVER, END };
GameState state;
sf::Font font;

void menuConstr() {
	state = END;

	if (!font.loadFromFile("data//img//font//batmfa.ttf"))
	{
		cout << "Font not found!" << endl;
		return;
	}

	state = MENU;
}

void runMenu() {
	sf::Text title("Tanks!", font, 80);
	title.setStyle(sf::Text::Bold);
	title.setPosition(WINDOW_WIDTH / 2 - title.getGlobalBounds().width / 2, 20);

	const int menuItems = 3;

	sf::Text menuText[menuItems];

	string str[] = { "Join", "Create","Exit" };
	for (int i = 0; i<menuItems; i++)
	{
		menuText[i].setFont(font);
		menuText[i].setCharacterSize(45);
		menuText[i].setString(str[i]);
		menuText[i].setPosition(WINDOW_WIDTH / 2 - menuText[i].getGlobalBounds().width / 2, 200 + i * 70);
	}

	while (state == MENU)
	{
		sf::Vector2f mouse(sf::Mouse::getPosition(window));
		sf::Event event;
	
		while (window.pollEvent(event))
		{	
			//create
			if (menuText[0].getGlobalBounds().contains(mouse) && event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left)
			{
				state = GAME_CREATE;
			}
			//join
			else if (menuText[1].getGlobalBounds().contains(mouse) && event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left)
			{
				state = GAME_JOIN;
			}
			//exit
			else if (menuText[2].getGlobalBounds().contains(mouse) && event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left)
			{
				state = END;
			}
		}
		for (int i = 0; i<menuItems; i++)
			if (menuText[i].getGlobalBounds().contains(mouse))
				menuText[i].setColor(sf::Color::Cyan);
			else menuText[i].setColor(sf::Color::White);

			window.clear();

			window.draw(title);
			for (int i = 0; i<menuItems; i++)
				window.draw(menuText[i]);

			window.display();
	}

}

void runGame() {
	playerController p1("data//img//p1//playerDown.png");//potrzeba 2 slashe

	tmx::TileMap map("data//img//maps//test_map.tmx");
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
}



int main()
{

	menuConstr();

	while (state != END)
	{
		switch (state)
		{
		case GameState::MENU:
			runMenu();
			break;
		case GameState::GAME_CREATE:
			runGame();
			break;
		case GameState::GAME_JOIN:
			runGame();
			break;
		}
	}
	
	return 0;
}
