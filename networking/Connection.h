#pragma once
#include <SFML\Network.hpp>

class Connection
{
public:
	Connection(sf::IpAddress ip);
	~Connection();

private:
	sf::IpAddress ip;
};

