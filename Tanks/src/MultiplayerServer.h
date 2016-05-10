#pragma once
#include <enet/enet.h>
#include <string>

class MultiplayerServer
{
public:
	MultiplayerServer();
	void start_server(int port);
	void stop_server();
	void send_packet(int channel, const char* pack);
	void listen();
private:
	int init_server();
	int connected_players_number = 0;
	int max_client_number;
	const char * c_przetworzone;
	std::string wiadomosc;
	std::string przetworzone;
	ENetHost * server;
	ENetAddress address;
	ENetPeer * peer[2] = { 0,0 };
};
