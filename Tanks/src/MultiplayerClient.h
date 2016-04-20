#pragma once
#include <string>
#include <enet/enet.h>

class MultiplayerClient
{
public:
	MultiplayerClient();
	void start_client(const char * ip, int port);
	void stop_client();
	void send_packet(int channel, const char* pack);
private:
	int init_client();
	void connect_to_server();
	ENetAddress address;
	ENetHost * client;
	ENetPeer *peer;
};
