#include "Connection.h"

bool Connection::hasConnection(std::vector<Connection>* connections, Connection connection)
{
	for (std::vector<Connection>::iterator it = connections->begin(); it != connections->end(); ++it)
	{
		if (it->ip == connection.GetIP() && it->port == connection.GetPort())
			return true;
	}

	return false;
}

sf::IpAddress Connection::GetIP()
{
	return ip;
}

unsigned short Connection::GetPort()
{
	return port;
}

Connection::Connection(sf::IpAddress ip, unsigned short port)
{
	this->ip = ip;
	this->port = port;
}


Connection::~Connection()
{
}
