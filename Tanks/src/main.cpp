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
#include "Collisions.h"


sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Tanks!", sf::Style::Titlebar | sf::Style::Close);
enum GameState { MENU, GAME_CREATE, GAME_JOIN, GAME_OVER, END };
GameState state;
sf::Font font;
MultiplayerServer serwer;
MultiplayerClient klient;
int whichClient=1;

sf::RectangleShape rect;
Collisions collision;
string stringAdressIP = "127.0.0.1";

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

	const int menuItems = 5;

	sf::Text menuText[menuItems];
	
	string ipAd = "IP: " + MultiplayerServer::get_server_ip();
	sf::Text ipAddressText;
	ipAddressText.setString(ipAd);
	ipAddressText.setPosition(10, 10);
	ipAddressText.setFont(font);
	ipAddressText.setCharacterSize(16);

	string str[] = { "Create", "Join","Exit", stringAdressIP, ipAd };
	for (int i = 0; i<menuItems; i++)
	{
		menuText[i].setFont(font);
		menuText[i].setCharacterSize(45);
		menuText[i].setString(str[i]);
		menuText[i].setPosition(WINDOW_WIDTH / 2 - menuText[i].getGlobalBounds().width / 2, 200 + i * 70);
		
	}
	menuText[3].setPosition(WINDOW_WIDTH / 2 - menuText[3].getGlobalBounds().width / 2 + 150, 270);
	menuText[1].setPosition(WINDOW_WIDTH / 2 - menuText[1].getGlobalBounds().width / 2 - 150, 200 + 70);


	


	while (state == MENU)
	{
		sf::Vector2f mouse(sf::Mouse::getPosition(window));
		sf::Event event;
		
	
		while (window.pollEvent(event))
		{	
			if (event.type == sf::Event::TextEntered)
			{
				if (event.text.unicode == 8) {
					stringAdressIP = stringAdressIP.substr(0, stringAdressIP.size() - 1);
					//cout << stringAdressIP << endl;

				}
				else if ((event.text.unicode < 58 && event.text.unicode > 47) || event.text.unicode == 46)
				{
					if (stringAdressIP.size() < 15) {
						stringAdressIP += static_cast<char>(event.text.unicode);
					}
					
					//cout << stringAdressIP << endl;
					
				}
				menuText[3].setString(stringAdressIP);
			}

			if (event.type == sf::Event::Closed)
				exit(0);

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

			str[3] = stringAdressIP;
		}

		for (int i = 0; i<menuItems-1; i++)
			if (menuText[i].getGlobalBounds().contains(mouse))
				menuText[i].setColor(sf::Color::Cyan);
			else menuText[i].setColor(sf::Color::White);

			ipAddressText.setColor(sf::Color::White);

			

			window.clear();

			window.draw(title);

			for (int i = 0; i<menuItems; i++)
				window.draw(menuText[i]);
			window.draw(ipAddressText);
			

			window.display();
	}

}


void backToMenu() {
	state = MENU;
	cout << "state: menu " << state << endl;

	//klient.stop_client();
	//serwer.stop_server();

	runMenu();
	
}

void runGame() {
	Logic logic;
	ClientLogic clLogic(whichClient);
	
	tmx::TileMap map("data//img//maps//test_map.tmx");
	map.ShowObjects();
	map.GetLayer("map").visible = true;
	map.GetLayer("collision").visible = false;

	std::this_thread::sleep_for(std::chrono::milliseconds(500));

	const char * ip = stringAdressIP.c_str();
	klient.start_client(ip, 1234);
	clLogic.listen(logic.init());
	while (window.isOpen())
	{
		sf::Event event;
		window.pollEvent(event);
		
		if (event.type == sf::Event::Closed)
			exit(0);

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
		//backToMenu();

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
