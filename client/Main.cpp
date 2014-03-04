#define PORT 54545

#include <iostream>
#include <SFML\Network.hpp>
#include <CompressedPacket.h>


int main(int argc, char* argv[])
{
	sf::IpAddress serverIp = "127.0.0.1";
	sf::UdpSocket socket;

	if (socket.bind(sf::Socket::AnyPort) != sf::Socket::Done)
	{
		// err
		return EXIT_FAILURE;
	}

	for (;;)
	{
		CompressedPacket packet;
		char input[1024];
		std::cin >> input;
		packet << input;

		if (socket.send(packet, serverIp, PORT))
		{
			// error
		}

		// Listen
		CompressedPacket reply;
		sf::IpAddress sender;
		unsigned short port;
		if (socket.receive(reply, sender, port) != sf::Socket::Done)
		{
			// err
		}

		char replyData[1024];
		reply >> replyData;

		std::cout << "Packet from server. Says: " << replyData << std::endl;

	}

	socket.unbind();
	return EXIT_SUCCESS;
}

