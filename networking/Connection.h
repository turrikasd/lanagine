#pragma once

#include <SFML\Network.hpp>
#include <vector>

class Connection
{
public:
	Connection(sf::IpAddress ip, unsigned short port);
	~Connection();

	sf::IpAddress GetIP();
	unsigned short GetPort();
	bool Equals(Connection other);

	static bool hasConnection(std::vector<Connection>* connections, Connection connection);

private:
	sf::IpAddress ip;
	unsigned short port;
};

