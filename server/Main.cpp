// Server.cpp : Defines the entry point for the console application.
//

#define PORT 54545

#include <iostream>
#include <UDPServer.h>
#include <ErrorReporter.h>
#include <thread>
#include <NET_CODES.h>
#include "World.h"
#include "Player.h"

nw::UDPServer udpServer;
World world;
bool listening;

void HandlePacket(sf::UdpSocket* socket, CompressedPacket packet, Connection pSender)
{
	sf::Int16 net_code;
	packet >> net_code;

	if (net_code == NC_LOGIN)
	{
		char name[32];
		packet >> name;

		int playerId = world.NewPlayer(&pSender, name); // Server will create new player

		for (std::vector<Player>::iterator it = world.players.begin(); it != world.players.end(); ++it)
		{
			if (it->playerId == playerId) // Special case, make sure new player knows his ID
			{
				{ // Send this to the owner
					CompressedPacket newPlayerPacket;
					newPlayerPacket << NC_NEW_YOU;
					newPlayerPacket << it->playerId << it->name << it->x << it->y << it->z;
					udpServer.SendOne(socket, newPlayerPacket, pSender);
				}

				{ // Send this to everyone else

				CompressedPacket newPlayerPacket;

				newPlayerPacket << NC_NEW_PLAYER;

				newPlayerPacket << it->playerId << it->name << it->x << it->y << it->z;
				udpServer.SendAllBut(socket, newPlayerPacket, pSender);
				}
			}

			else // Send normally to everyone
			{
				CompressedPacket newPlayerPacket;

				newPlayerPacket << NC_NEW_PLAYER;

				newPlayerPacket << it->playerId << it->name << it->x << it->y << it->z;
				udpServer.SendAll(socket, newPlayerPacket);
			}
		}

		return;
	}

	if (net_code == NC_MOVEMENT)
	{
		int playerID;
		int x, y, z;
		packet >> playerID >> x >> y >> z;

		world.MovePlayer(playerID, x, y, z);

		CompressedPacket playerMovementPacket;
		playerMovementPacket << NC_MOVEMENT << playerID << x << y << z;
		udpServer.SendAll(socket, playerMovementPacket);
	}
}

void UDPListen()
{
	sf::UdpSocket socket;

	int err;

	err = udpServer.ServerRegisterSocket(&socket, PORT);
	if (err)
	{
		nw::Report(err);
		return;
	}

	listening = true;

	while (listening)
	{
		CompressedPacket packet;

		Connection connection = udpServer.GetNextPacket(&socket, &packet); // Blocking

		std::thread msgThread = std::thread(&HandlePacket, &socket, packet, connection);
		msgThread.detach();
	}

	socket.unbind();
}

int main(int argc, char* argv[])
{
	std::thread NetListenThread = std::thread(&UDPListen);
	NetListenThread.detach();

	//udpServer.ServerEnterListenMode();

	int a;
	std::cin >> a;

	return EXIT_SUCCESS;
}

