#include "enet/enet.h"
#include "MultiplayerClient.h"
#include <conio.h>

using namespace std;

int main_client()
{
	MultiplayerClient klient;

	klient.start_client("localhost", 1234);

	_getch();
	return 0;
}