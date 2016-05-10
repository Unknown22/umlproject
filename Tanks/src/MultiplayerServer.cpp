#include "MultiplayerServer.h"
#include <enet/enet.h>
#include <cstdio>
#include <iostream>
#include <string>
#include <cstring>
#include "Logic.h"
#include "ClientLogic.h"

MultiplayerServer::MultiplayerServer()
{
	init_server();
}

void MultiplayerServer::start_server(int _port = 1234)
{
	int _max_client_number = 2;
	max_client_number = _max_client_number;
	/* Bind the server to the default localhost.     */
	/* A specific host address can be specified by   */
	/* enet_address_set_host (& address, "x.x.x.x"); */
	address.host = ENET_HOST_ANY;
	//enet_address_set_host(&address, "localhost");
	/* Bind the server to port 1234. */
	address.port = _port;
	server = enet_host_create(&address /* the address to bind the server host to */,
		max_client_number      /* allow up to 32 clients and/or outgoing connections */,
		2      /* allow up to 2 channels to be used, 0 and 1 */,
		0      /* assume any amount of incoming bandwidth */,
		0      /* assume any amount of outgoing bandwidth */);
	if (server == NULL)
	{
		fprintf(stderr,
			"An error occurred while trying to create an ENet server host.\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		std::cout << "Serwer dziala" << std::endl;
	}
}

void MultiplayerServer::stop_server()
{
	enet_host_destroy(server);
	std::cout << "Niszcze server" << std::endl;
}

void MultiplayerServer::send_packet(int _channel, const char* _pack)
{
	/* Create a reliable packet of size 7 containing "packet\0" */
	ENetPacket * packet = enet_packet_create(_pack,
		strlen(_pack) + 1,
		ENET_PACKET_FLAG_RELIABLE);


	/* Send the packet to the peer over channel id 0. */
	/* One could also broadcast the packet by         */
	/* enet_host_broadcast (host, 0, packet);         */
	if (peer[0] != 0)
	{
		enet_peer_send(peer[0], _channel, packet);
	}
	if (peer[1] != 0)
	{
		enet_peer_send(peer[1], _channel, packet);
	}
	/* One could just use enet_host_service() instead. */
	enet_host_flush(server);
}

int MultiplayerServer::init_server()
{
	if (enet_initialize() != 0)
	{
		fprintf(stderr, "An error occurred while initializing ENet.\n");
		return EXIT_FAILURE;
	}
	atexit(enet_deinitialize);
	return 0;
}

void MultiplayerServer::listen()
{
	Logic logic;

	char buf[256];
	enet_address_get_host_ip(&address, buf, sizeof(buf));
	//std::cout << "Nasluchuje na: " << buf << ":" << address.port << std::endl;
	ENetEvent event;
	// processing incoming events:
	while (enet_host_service(server, &event, 1000) >= 0)
	{
		//printf("Checking Incoming\n");
		switch (event.type)
		{
		case ENET_EVENT_TYPE_CONNECT:
		{
			char bufadres[256];
			enet_address_get_host_ip(&event.peer->address, bufadres, sizeof(bufadres));
			std::cout << "Nowe polaczenie nawiazane od: " << bufadres << ":" << event.peer->address.port << std::endl;

			std::string port_str = std::to_string(event.peer->address.port);

			std::string nazwa = std::string(bufadres) + ":" + port_str;

			std::string * p_nazwa = &nazwa;
			event.peer->data = p_nazwa;
			peer[connected_players_number] = event.peer;
			connected_players_number++;
			break;
		}
		case ENET_EVENT_TYPE_RECEIVE:
			char bufadres[256];
			enet_address_get_host_ip(&event.peer->address, bufadres, sizeof(bufadres));
			//std::cout << bufadres << ":" << event.peer->address.port << " przesyla wiadomosc " << (char*)event.packet->data << " na kanale " << (u_int)event.channelID << std::endl;
			fflush(stdout);
			//std::cout << (char*)event.packet->data << std::endl;
			wiadomosc = (char*)event.packet->data;
			logic.listen(wiadomosc);
			przetworzone = logic.send();
			cout << przetworzone << endl;
			c_przetworzone = przetworzone.c_str();
			enet_packet_destroy(event.packet); // clean up the packet now that we're done using it
			send_packet(0, c_przetworzone);
			break;
		case ENET_EVENT_TYPE_DISCONNECT:
			printf("  host disconnected.\n");
			fflush(stdout);
			event.peer->data = 0; // reset the peer's client information.
			free(event.peer->data);

			for (int i = 0; i < connected_players_number; i++)
			{
				if (peer[i]->address.host == event.peer->address.host
					&& peer[i]->address.port == event.peer->address.port)
				{
					peer[i] = 0;
				}
			}
		default:
			break;
		}
	}
}
