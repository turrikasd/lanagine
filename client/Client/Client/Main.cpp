#define PORT 54545

#include <iostream>
#include <SFML\Network.hpp>


int main(int argc, char* argv[])
{
	for (;;)
	{
		char data[100];
		std::cin >> data;

		sf::IpAddress serverIp = sf::IpAddress::LocalHost;
		sf::UdpSocket socket;

		if (socket.send(data, sizeof(data), serverIp, PORT))
		{
			// error
		}
	}


	int holdInt;
	std::cin >> holdInt;


	return EXIT_SUCCESS;
}

