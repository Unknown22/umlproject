#include "enet/enet.h"
#include "MultiplayerServer.h"
#include <thread>
#include <conio.h>

using namespace std;

void listen_server(MultiplayerServer * _serwer)
{
	_serwer->listen();
}

int main_server()
{
	MultiplayerServer serwer;

	serwer.start_server(1234, 2);

	thread tServer(listen_server, &serwer);
	tServer.join();

	serwer.stop_server();

	_getch();
	return 0;
}