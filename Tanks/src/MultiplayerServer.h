#pragma once
#include <enet/enet.h>

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
	ENetHost * server;
	ENetAddress address;
	ENetPeer *peer;
};
