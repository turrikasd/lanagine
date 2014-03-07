#include "UDPServer.h"
#include "ErrorReporter.h"

using namespace nw;

int UDPServer::ServerRegisterSocket(sf::UdpSocket* socket, unsigned short listenPort)
{
	if (listenPort == 0 || listenPort > 65535)
		return NETWORK_ERROR_INVALID_PORT;

	this->listenPort = listenPort;

	if (socket->bind(listenPort) != sf::Socket::Done)
	{
		Report(NETWORK_ERROR_SOCKET_NOT_BOUND);
		return NETWORK_ERROR_SOCKET_NOT_BOUND;
	}
		
	return NETWORK_NO_ERROR;
}

int UDPServer::GetNextPacket(sf::UdpSocket* socket, CompressedPacket* pPacket, Connection* pConnection)
{
	sf::IpAddress senderIp;
	unsigned short port;

	if (socket->receive(*pPacket, senderIp, port) != sf::Socket::Done)
	{
		Report(NETWORK_ERROR_UDP_PACKET_FAULT);
		return NETWORK_ERROR_UDP_PACKET_FAULT;
	}

	if (!Connection::hasConnection(&connections, Connection(senderIp, port)))
	{
		std::vector<Connection>::iterator it;
		it = connections.end();
		connections.insert(it, Connection(senderIp, port));
	}

	pConnection = &Connection(senderIp, port);

	return NETWORK_NO_ERROR;
}

void UDPServer::SendAll(sf::UdpSocket* socket, CompressedPacket packet)
{
	for (std::vector<Connection>::iterator it = connections.begin(); it != connections.end(); ++it)
	{
		socket->send(packet, it->GetIP(), it->GetPort());
	}
}

UDPServer::UDPServer()
{
}


UDPServer::~UDPServer()
{
	//pSocket->unbind();
}
