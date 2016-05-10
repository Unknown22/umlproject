#pragma once
#include <string>
#include <enet/enet.h>

class MultiplayerClient
{
public:
	MultiplayerClient();
	void start_client(const char * ip, int port);
	void stop_client();
	void send_packet(int channel);
	void set_message(std::string message);
	void listen();
	std::string get_info_from_server();
private:
	int init_client();
	void connect_to_server();
	std::string od_serwera;
	std::string message;
	ENetAddress address;
	ENetHost* client;
	ENetPeer* peer;
};
