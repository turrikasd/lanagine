#include "UDPServer.h"
#include "ErrorReporter.h"

using namespace nw;

int UDPServer::ServerRegisterSocket(unsigned short listenPort)
{
	if (listenPort == 0 || listenPort > 65535)
		return NETWORK_ERROR_INVALID_PORT;

	sf::UdpSocket socket;
	this->listenPort = listenPort;
		
	return NETWORK_NO_ERROR;
}

int UDPServer::ServerEnterListenMode()
{
	listening = true;

	listenThread = std::thread(&UDPServer::ListenLoop, this);

	return NETWORK_NO_ERROR;
}

void UDPServer::ListenLoop()
{
	if (socket.bind(listenPort) != sf::Socket::Done)
	{
		Report(NETWORK_ERROR_SOCKET_NOT_BOUND);
		return;
	}

	while (listening)
	{
		sf::Packet packet;
		sf::IpAddress sender;
		unsigned short port;

		if (socket.receive(packet, sender, port) != sf::Socket::Done)
		{
			Report(NETWORK_ERROR_UDP_PACKET_FAULT);
			continue;
		}

		std::thread msgThread = std::thread(&UDPServer::HandlePacket, this, packet, sender);
		msgThread.detach();
	}
}

void UDPServer::HandlePacket(sf::Packet packet, sf::IpAddress sender)
{
	Report(NETWORK_NO_ERROR);
}

UDPServer::UDPServer()
{
}


UDPServer::~UDPServer()
{
	socket.unbind();
}
