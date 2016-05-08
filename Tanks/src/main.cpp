#include <SFML/Graphics.hpp>
#include "playerController.h"
#include <iostream>
#include "ConstantVariables.h"
#include "STP/TMXLoader.hpp"
#include <string>
#include "Logic.h"
#include "ClientLogic.h"

sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Tanks!");
enum GameState { MENU, GAME_CREATE, GAME_JOIN, GAME_OVER, END };
GameState state;
sf::Font font;

void menuConstr() {
	state = END;

	if (!font.loadFromFile("data//font//batmfa.ttf"))
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
	Logic logic;
	ClientLogic clLogic;
	
	tmx::TileMap map("data//img//maps//test_map.tmx");
	map.ShowObjects();
	map.GetLayer("map").visible = true;
	map.GetLayer("collision").visible = false;

	clLogic.listen(logic.init());
	while (window.isOpen())
	{
		sf::Event event;
		window.pollEvent(event);
		
		if (event.type == sf::Event::Closed)
			window.close();

		logic.listen(clLogic.handleKeyboard(event));
		clLogic.listen(logic.send());
		window.clear();
		window.draw(map);
		typedef std::map<std::string, SpriteClient>::iterator it_type;
		for (it_type iterator = clLogic.spriteMap.begin(); iterator != clLogic.spriteMap.end(); iterator++) {
			window.draw(iterator->second);
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
