#pragma once

#define DATA_MAX_SIZE 100

#include "NetworkErrorCodes.h"
#include <SFML\Network.hpp>
#include <vector>
#include "Connection.h"
#include <thread>

namespace nw
{

	class UDPServer
	{
	public:
		UDPServer();
		~UDPServer();

		int ServerRegisterSocket(unsigned short listenPort);
		int ServerEnterListenMode();

	private:
		void ListenLoop();
		void HandlePacket(sf::Packet packet, sf::IpAddress ip);

	private:
		bool listening;
		unsigned short listenPort;
		sf::UdpSocket socket;
		std::vector<Connection> connections;
		std::thread listenThread;

	};

}