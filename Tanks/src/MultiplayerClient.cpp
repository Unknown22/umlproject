#include "MultiplayerClient.h"
#include <iostream>

MultiplayerClient::MultiplayerClient()
{
	init_client();
}

void MultiplayerClient::start_client(const char * _ip, int _port)
{
	enet_address_set_host(&address, _ip);
	address.port = _port;

	client = enet_host_create(NULL /* create a client host */,
		1 /* only allow 1 outgoing connection */,
		2 /* allow up 2 channels to be used, 0 and 1 */,
		0 /* 56K modem with 56 Kbps downstream bandwidth */,
		0 /* 56K modem with 14 Kbps upstream bandwidth */);
	if (client == NULL)
	{
		fprintf(stderr,
			"An error occurred while trying to create an ENet client host.\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		std::cout << "Klient dziala" << std::endl;
		connect_to_server();
	}
}

void MultiplayerClient::stop_client()
{
	enet_host_destroy(client);
	std::cout << "Niszcze klienta" << std::endl;
}

void MultiplayerClient::send_packet(int _channel)
{
	const char* message_c = message.c_str();
	/* Create a reliable packet of size 7 containing "packet\0" */
	ENetPacket * packet = enet_packet_create(message_c,
		strlen(message_c) + 1,
		ENET_PACKET_FLAG_UNRELIABLE_FRAGMENT);


	/* Send the packet to the peer over channel id 0. */
	/* One could also broadcast the packet by         */
	/* enet_host_broadcast (host, 0, packet);         */

	enet_peer_send(peer, _channel, packet);
	/* One could just use enet_host_service() instead. */
	enet_host_flush(client);
}

void MultiplayerClient::set_message(std::string _message)
{
	this->message = _message;
}

int MultiplayerClient::init_client()
{
	if (enet_initialize() != 0)
	{
		fprintf(stderr, "An error occurred while initializing ENet.\n");
	}
	atexit(enet_deinitialize);

	return 0;
}

void MultiplayerClient::connect_to_server()
{
	ENetEvent event;

	/* Initiate the connection, allocating the two channels 0 and 1. */

	peer = enet_host_connect(client, &address, 2, 0);
	peer->data = 0; // use this as mark that connection is not yet acknowledged
	if (peer == NULL)
	{
		fprintf(stderr,
			"No available peers for initiating an ENet connection.\n");
		exit(EXIT_FAILURE);
	}
	/* Wait up to 5 seconds for the connection attempt to succeed. */
	if (enet_host_service(client, &event, 5000) > 0 &&
		event.type == ENET_EVENT_TYPE_CONNECT)
	{
		puts("Connection succeeded.");
	}
	else
	{
		/* Either the 5 seconds are up or a disconnect event was */
		/* received. Reset the peer in the event the 5 seconds   */
		/* had run out without any significant event.            */
		enet_peer_reset(peer);
		puts("Connection failed.");
	}
}


void MultiplayerClient::listen()
{
	ENetEvent event;
	// processing incoming events:
	while (enet_host_service(client, &event, 1000) >= 0)
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
			peer = event.peer;
			break;
		}
		case ENET_EVENT_TYPE_RECEIVE:
			char bufadres[256];
			enet_address_get_host_ip(&event.peer->address, bufadres, sizeof(bufadres));
			std::cout << bufadres << ":" << event.peer->address.port << " przesyla wiadomosc " << (char*)event.packet->data << " na kanale " << (u_int)event.channelID << std::endl;
			fflush(stdout);
			enet_packet_destroy(event.packet); // clean up the packet now that we're done using it
			break;
		case ENET_EVENT_TYPE_DISCONNECT:
			printf("  host disconnected.\n");
			fflush(stdout);
			event.peer->data = 0; // reset the peer's client information.
			free(event.peer->data);
			peer = 0;
		default:
			break;
		}
	}
}