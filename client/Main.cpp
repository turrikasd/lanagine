#define PORT 54545

#include <iostream>
#include <SFML\Network.hpp>


int main(int argc, char* argv[])
{
	sf::IpAddress serverIp = sf::IpAddress::LocalHost;
	sf::UdpSocket socket;

	if (socket.bind(sf::Socket::AnyPort) != sf::Socket::Done)
	{
		// err
		return EXIT_FAILURE;
	}

	for (;;)
	{
		char data[100];
		std::cin >> data;

		if (socket.send(data, sizeof(data), serverIp, PORT))
		{
			// error
		}

		// Listen
		char reply[100];
		std::size_t received;
		sf::IpAddress sender;
		unsigned short port;
		if (socket.receive(reply, 100, received, sender, port) != sf::Socket::Done)
		{
			// err
		}

		std::cout << received << " bytes from server. Says: " << reply << std::endl;

	}

	socket.unbind();
	return EXIT_SUCCESS;
}

