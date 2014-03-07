#pragma once

#define DATA_MAX_SIZE 100

#include "NetworkErrorCodes.h"
#include <SFML\Network.hpp>
#include <vector>
#include "Connection.h"
#include <thread>
#include "CompressedPacket.h"
#include "NET_CODES.h"

namespace nw
{

	class UDPServer
	{
	public:
		UDPServer();
		~UDPServer();

		int ServerRegisterSocket(sf::UdpSocket* socket, unsigned short listenPort);
		Connection GetNextPacket(sf::UdpSocket* socket, CompressedPacket* pPacket);

		void SendAll(sf::UdpSocket* socket, CompressedPacket packet);
		void SendAllBut(sf::UdpSocket* socket, CompressedPacket packet, Connection skip);
		void SendOne(sf::UdpSocket* socket, CompressedPacket packet, Connection recipient);

	private:
		bool listening;
		unsigned short listenPort;
		std::vector<Connection> connections;
		std::thread listenThread;

	};

}