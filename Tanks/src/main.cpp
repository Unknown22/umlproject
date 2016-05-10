#include <SFML/Graphics.hpp>
#include "playerController.h"
#include <iostream>
#include "ConstantVariables.h"
#include "STP/TMXLoader.hpp"
#include <string>
#include <chrono>
#include <thread>
#include "Logic.h"
#include "ClientLogic.h"
#include "MultiplayerServer.h"
#include "MultiplayerClient.h"

sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Tanks!");
enum GameState { MENU, GAME_CREATE, GAME_JOIN, GAME_OVER, END };
GameState state;
sf::Font font;
MultiplayerServer serwer;
MultiplayerClient klient;
int whichClient=1;

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

	string str[] = { "Create", "Join","Exit" };
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
				whichClient = 1;
			}
			//join
			else if (menuText[1].getGlobalBounds().contains(mouse) && event.type == sf::Event::MouseButtonReleased && event.key.code == sf::Mouse::Left)
			{
				state = GAME_JOIN;
				whichClient = 2;
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
	ClientLogic clLogic(whichClient);
	
	tmx::TileMap map("data//img//maps//test_map.tmx");
	map.ShowObjects();
	map.GetLayer("map").visible = true;
	map.GetLayer("collision").visible = false;

	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	klient.start_client("localhost", 1234);

	
	clLogic.listen(logic.init());
	while (window.isOpen())
	{
		sf::Event event;
		window.pollEvent(event);
		
		if (event.type == sf::Event::Closed)
			window.close();

		if(window.hasFocus())
		{
			klient.set_message(clLogic.handleKeyboard(event));
			//cout << clLogic.handleKeyboard(event) << endl;
			klient.send_packet(0);
		}
		
		string pozycje;
		pozycje = klient.get_info_from_server();
		
		//logic.listen(clLogic.handleKeyboard(event));
		clLogic.listen(pozycje);
		window.clear();
		window.draw(map);
		typedef std::map<std::string, SpriteClient>::iterator it_type;
		for (it_type iterator = clLogic.spriteMap.begin(); iterator != clLogic.spriteMap.end(); iterator++) {
			window.draw(iterator->second);
		}
		
		window.display();
	}

	klient.stop_client();

}

void listen_server(MultiplayerServer * _serwer)
{
	_serwer->listen();
}


void runServer()
{
	serwer.start_server(1234);
	std::thread tServer(listen_server, &serwer);
	runGame();
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
			runServer();
			break;
		case GameState::GAME_JOIN:
			runGame();
			break;
		}
	}
	
	return 0;
}
