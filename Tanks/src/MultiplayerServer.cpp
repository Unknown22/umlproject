#include "MultiplayerServer.h"
#include <enet/enet.h>
#include <cstdio>
#include <iostream>
#include <string>

MultiplayerServer::MultiplayerServer()
{
	init_server();
}

void MultiplayerServer::start_server(int _port = 1234)
{
	/* Bind the server to the default localhost.     */
	/* A specific host address can be specified by   */
	/* enet_address_set_host (& address, "x.x.x.x"); */
	address.host = ENET_HOST_ANY;
	//enet_address_set_host(&address, "localhost");
	/* Bind the server to port 1234. */
	address.port = _port;
	server = enet_host_create(&address /* the address to bind the server host to */,
		2      /* allow up to 32 clients and/or outgoing connections */,
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
	enet_peer_send(peer, _channel, packet);
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
	char buf[256];
	enet_address_get_host_ip(&address, buf, sizeof(buf));
	std::cout << "Nasluchuje na: " << buf << ":" << address.port << std::endl;
	ENetEvent event;
	// processing incoming events:
	while (enet_host_service (server, &event, 1000) >= 0)
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
			event.peer->data;
			peer=event.peer;
			break;
		}
		case ENET_EVENT_TYPE_RECEIVE:
			printf("%x says %s on channel %u\n",
				(char*)event.peer -> data,event.packet -> data,event.channelID);
			fflush(stdout);
			enet_packet_destroy (event.packet); // clean up the packet now that we're done using it
			send_packet(0,"Data Received") ;
			break;
		case ENET_EVENT_TYPE_DISCONNECT:
			printf("  host disconnected.\n");
			fflush(stdout);
			free(event.peer -> data);
			event.peer -> data = 0; // reset the peer's client information.
			peer=0;
		default:
			break;
		}
	}
}
