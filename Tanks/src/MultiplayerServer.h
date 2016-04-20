#pragma once
#include <enet/enet.h>

class MultiplayerServer
{
public:
	MultiplayerServer();
	void start_server(int port, int max_client_number);
	void stop_server();
	void send_packet(int channel, const char* pack);
	void listen();
private:
	int init_server();

	int max_client_number;
	ENetHost * server;
	ENetAddress address;
	ENetPeer * peer;
};
