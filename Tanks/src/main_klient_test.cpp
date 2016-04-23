#include "enet/enet.h"
#include "MultiplayerClient.h"
#include <conio.h>
#include <iostream>
#include <thread>

using namespace std;

void listen_client(MultiplayerClient * _client)
{
	_client->listen();
}

void send_message(MultiplayerClient klient, string message)
{
	while(true)
	{
		cin >> message;
		klient.set_message(message);
		klient.send_packet(0);
	}
}

int main_klient()
{
	MultiplayerClient klient;

	klient.start_client("localhost", 1234);

	string message;

	thread tClient(listen_client, &klient);
	thread tSendMessage(send_message, klient, message);
	tClient.join();
	tSendMessage.join();

	_getch();
	return 0;
}
