#include "enet/enet.h"
#include "MultiplayerServer.h"
#include <thread>
#include <conio.h>

using namespace std;

void listen_server(MultiplayerServer * _serwer)
{
	_serwer->listen();
}

int main()
{
	MultiplayerServer serwer;

	serwer.start_server(1234);

	thread tServer(listen_server, &serwer);

	_getch();
	return 0;
}