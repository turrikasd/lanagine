// Server.cpp : Defines the entry point for the console application.
//

#define PORT 54545

#include <iostream>
#include <SFML\Network.hpp>


int main(int argc, char* argv[])
{
	sf::UdpSocket socket;

	if (socket.bind(PORT) != sf::Socket::Done)
	{
		//err
		return EXIT_FAILURE;
	}

	for (;;)
	{
		char data[100];
		std::size_t received;
		sf::IpAddress sender;
		unsigned short port;
		if (socket.receive(data, 100, received, sender, port) != sf::Socket::Done)
		{
			//err
		}

		std::cout << received << " bytes from " << sender << ". Says: " << data << std::endl;
	}


	int holdInt;
	std::cin >> holdInt;

	socket.unbind();
	return EXIT_SUCCESS;
}

