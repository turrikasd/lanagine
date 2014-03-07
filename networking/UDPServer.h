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
		int GetNextPacket(sf::UdpSocket* socket, CompressedPacket* pPacket, Connection* pConnection);

		void SendAll(sf::UdpSocket* socket, CompressedPacket packet);

	private:
		bool listening;
		unsigned short listenPort;
		std::vector<Connection> connections;
		std::thread listenThread;

	};

}